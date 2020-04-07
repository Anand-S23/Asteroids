// Includes 
#include "main.h"

void initGame()
{
    // seeds the rand with time
    srand(time(NULL));

    CreateWindow("Asteroids", SCREEN_WIDTH, SCREEN_HEIGHT);

    // Initializes the player
    player.x = SCREEN_WIDTH / 2;
    player.y = (3 * SCREEN_HEIGHT) / 4;
    player.angle = 0.0;
    player.health = 100; 
    player.texture = loadTexture("assests/playerShip2_blue.png");

    // Creates the initial asteroids -> 8 random (big or med) and 2 small
    for (int i = 0; i < 8; ++i) 
    {
        int size = randInt(1, 2);
        createAsteroid(asteroids, size);
    }

    for (int i = 0; i < 2; ++i)
    {
        createAsteroid(asteroids, 0);
    }

    
}

void handleMovement()
{
	// Player movement 
	if (app.up)
    {
       	player.y -= 4.0*cos(player.angle*RAD);
        player.x += 4.0*sin(player.angle*RAD);
    }
	if (app.right)
    {
	    player.angle += 2.5; 
    }
    if (app.left)
    {
	    player.angle -= 2.5;
    }
    if (app.space)
    {
        createBullet(bullets, player.x, player.y, player.angle);
        app.space = 0;
    }

    // Fixes the angles, so the angles don't increase to decrease to large numbers
    if (player.angle < -180.0)
        player.angle = 180.0;
    if (player.angle > 180.0)
        player.angle = -180.0; 

    // Keeps payer on screen
    if (player.x < -20.0)
        player.x = SCREEN_WIDTH;
    if (player.x > SCREEN_WIDTH+20)
        player.x = 270.0;
    if (player.y < -20.0)
        player.y = SCREEN_HEIGHT;
    if (player.y > SCREEN_HEIGHT+20)
        player.y = 0.0;

    // loop through to update the Bullets
    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        if (bullets[i])
        {
            bullets[i]->x += (6.0*sin(bullets[i]->angle*RAD));
            bullets[i]->y -= (6.0*cos(bullets[i]->angle*RAD));

            if (bullets[i]->x < 0 || bullets[i]->x > SCREEN_WIDTH || bullets[i]->y < 0 || bullets[i]->y > SCREEN_HEIGHT)
                destroyBullet(bullets, i);
        }
    }

	// loop through to update the Asteroids
    for (int i = 0; i < MAX_AST; ++i)
    {
        if (asteroids[i])
        {
            asteroids[i]->angle += 0.9;
            asteroids[i]->x += asteroids[i]->dx;
            asteroids[i]->y += asteroids[i]->dy;
    
            if (asteroids[i]->dx < 0 && asteroids[i]->x < -30)
                asteroids[i]->x = (double) SCREEN_WIDTH;
            if (asteroids[i]->dx > 0 && asteroids[i]->x > SCREEN_WIDTH+30)
                asteroids[i]->x = 0.0;
            if (asteroids[i]->dy < 0 && asteroids[i]->y < -30)
                asteroids[i]->y = (double) SCREEN_HEIGHT;
            if (asteroids[i]->dy > 0 && asteroids[i]->y > SCREEN_HEIGHT+30)
                asteroids[i]->y = 0.0;
        }
    }
}

void collisions()
{
    for (int i = 0; i < MAX_AST; ++i) 
    {
        if (asteroids[i])
        {
            playerCollision(asteroids[i], player);
            if (app.playerCollision)
            {
                player.health -= 1;
                app.playerCollision = 0;
            }
        }

        for (int j = 0; j < MAX_BULLETS; ++j)
        {
            if (asteroids[i] && bullets[j])
            {
                bulletCollision(asteroids[i], bullets[j]);

                if (app.bulletCollision)
                {
                    double x = asteroids[i]->x;
                    double y = asteroids[i]->y; 
                    int size = asteroids[i]->size;

                    destroyAsteroid(asteroids, i);
                    destroyBullet(bullets, j);
                    app.bulletCollision = 0;
                    if (size > 0)
                    {
                        placeAsteroid(asteroids, x, y, size - 1);
                        placeAsteroid(asteroids, x, y, size - 1);
                    }
                }
            }
        }
    }
}

void update(SDL_Texture* bgImg, SDL_Texture* health, SDL_Texture* green, SDL_Texture* red)
{
    // Blits the bg, bullets, player and asteroids in that order
    blit(bgImg, 0, 0, 1280, 720);

    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        if (bullets[i])
        {
            blitRotated(bullets[i]->texture, bullets[i]->x, bullets[i]->y, bullets[i]->angle);
        }
    }
  
    blitPlayer(player.texture, player.x, player.y, player.angle);

    SDL_Rect a, rect;
    SDL_QueryTexture(player.texture, NULL, NULL, &a.w, &a.h);
    blit(green, player.x - (a.w/2 - 35), player.y, a.w - 70, a.h);

    // loop through the list of Asteroid and blit
    for (int i = 0; i < MAX_AST; ++i)
    {
        if (asteroids[i])
        {
            blitRotated(asteroids[i]->texture, asteroids[i]->x, asteroids[i]->y, asteroids[i]->angle);
        }
    }

    blitRotated(health, 25.0, 25.0, 0.0);
    blit(red, 48, 8, 102*3, 34);
    blit(green, 51, 10, player.health*3, 30);
}

void gameMenu(SDL_Texture* bgImg, SDL_Texture* title)
{
    blit(bgImg, 0, 0, 1280, 720);
    blitRotated(title, SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0, 0.0);

    if (app.space == 1)
    {
        app.space = 0; 
        app.screen = 1;
    }
}

// Main Loop 
int main(int argc, char* argv)
{
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));

    initGame();
    SDL_Texture* title = loadTexture("assests/title.png");
    SDL_Texture* bgImg = loadTexture("assests/space-2.png");
    SDL_Texture* health = loadTexture("assests/heart.png");
    SDL_Texture* green = loadTexture("assests/green.png");
    SDL_Texture* red = loadTexture("assests/red.png");
    app.screen = 0;
	
    atexit(cleanup);
	
    while (1)
    {
        switch(app.screen)
        {
            case 0: 
                prepareScene();
                doInput();
                gameMenu(bgImg, title);
                presentScene();
                SDL_Delay(16);
                break;
            case 1:
                prepareScene();
                doInput();
                handleMovement();
                update(bgImg, health, green, red);
                collisions();
                presentScene();
                SDL_Delay(16);
                break;
            case 2: 
                break;
        }
    }

    return 0;
}
