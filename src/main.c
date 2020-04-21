// Includes 
#include "main.h"

void reset() 
{
    for (int i = 0; i < MAX_AST; ++i)
    {
        asteroids[i] = NULL;
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i] = NULL; 
    }

    // Initializes the player
    player.x = SCREEN_WIDTH / 2;
    player.y = (3 * SCREEN_HEIGHT) / 4;
    player.angle = 0.0;

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

void initGame()
{
    // seeds the rand with time
    srand(time(NULL));

    CreateWindow("Asteroids", SCREEN_WIDTH, SCREEN_HEIGHT);
    
    reset();
    player.lives = 3;
    player.texture = loadTexture("assests/playerShip2_blue.png");
    app.screen = 0;
    app.score = 0;
    app.font = TTF_OpenFont("assests/kenvector_future_thin.ttf", 32);
}

void gameRest() 
{
    reset();
    player.lives = 3;
    player.texture = loadTexture("assests/playerShip2_blue.png");
    app.screen = 0;
    app.score = 0;
    app.font = TTF_OpenFont("assests/kenvector_future_thin.ttf", 32);
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
        Mix_PlayChannel(-1, app.shot, 0);
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
        if (asteroids[i] && playerCollision(asteroids[i], player))
        {
            destroyAsteroid(asteroids, i);
            player.lives--;
            //printf("%d\n", player.lives);
            reset();
            if (player.lives <= 0) 
            { 
                addScore(app.score); 
                app.screen = 3; 
            }
            else
            {
                app.screen = 2;
            }
            //printf("%d\n", app.screen);
        }

        for (int j = 0; j < MAX_BULLETS; ++j)
        {
            if (asteroids[i] && bullets[j] && bulletCollision(asteroids[i], bullets[j]))
            {
                double x = asteroids[i]->x;
                double y = asteroids[i]->y; 
                int size = asteroids[i]->size;

                destroyAsteroid(asteroids, i);
                destroyBullet(bullets, j);
                if (size > 0)
                {
                   placeAsteroid(asteroids, x, y, size - 1);
                   placeAsteroid(asteroids, x, y, size - 1);
                }

                if (size == 0) { app.score += 800; }
                if (size == 1) { app.score += 400; }
                if (size == 2) { app.score += 200; }
            }
        }
    }
}

void update(SDL_Texture* bgImg, SDL_Texture* health, SDL_Texture* life, SDL_Texture* green)
{
    // Blits the bg, bullets, player and asteroids in that order
    blit(bgImg, 0, 0, 1280, 720);

    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        if (bullets[i])
        {
            SDL_Rect b;
            SDL_QueryTexture(bullets[i]->texture, NULL, NULL, &b.w, &b.h);
            blitRotated(bullets[i]->texture, bullets[i]->x, bullets[i]->y, bullets[i]->angle);
            //blit(green, bullets[i]->x - b.w / 2, bullets[i]->y - b.h / 2, b.w, b.h);
        }
    }
  
    blitPlayer(player.texture, player.x, player.y, player.angle);

    SDL_Rect a;
    SDL_QueryTexture(player.texture, NULL, NULL, &a.w, &a.h);
    // blit(green, player.x - (a.w/2 - 35) * sin(player.angle * RAD), player.y * cos(player.angle * RAD), a.w - 70, a.h);
    // SDL_Rect rect = {player.x - (a.w/2 - 35), player.y, (a.w - 70) * cos(player.angle*RAD), a.h*sin(player.angle*RAD)};
    // SDL_RenderDrawRect(app.renderer, &rect);

    // loop through the list of Asteroid and blit
    for (int i = 0; i < MAX_AST; ++i)
    {
        if (asteroids[i])
        {
            SDL_Rect a;
            SDL_QueryTexture(asteroids[i]->texture, NULL, NULL, &a.w, &a.h);
            blitRotated(asteroids[i]->texture, asteroids[i]->x, asteroids[i]->y, asteroids[i]->angle);
            blit(green, asteroids[i]->x - a.w / 2 + 10, asteroids[i]->y - a.h / 2 + 10, a.w - 20, a.h - 20);
        }
    }

    blitRotated(health, 25.0, 25.0, 0.0);
    if (player.lives >= 1) { blitRotated(life, 70.0, 25.0, 0.0); }
    if (player.lives >= 2) { blitRotated(life, 120.0, 25.0, 0.0); }
    if (player.lives == 3) { blitRotated(life, 170.0, 25.0, 0.0); }

    SDL_Color textColor = { 255, 255, 255 };
    char text [33];
    itoa(app.score, text, 10);
    SDL_Surface* scoreDisplay = TTF_RenderText_Solid(app.font, text, textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(app.renderer, scoreDisplay);
    blitRotated(scoreTexture, 1200.0, 25.0, 0);
}

void checkPlay(int state)
{
    if (app.space && state == 2) { app.screen = 1; }
    if (app.space && state == 3) { gameRest(); app.screen = 0; }
}

void scoreScreen(SDL_Texture* over)
{
    blit(over, -1, 0, 1280, 720);
}

// Main Loop 
int main(int argc, char* argv)
{
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));

    initGame();
    app.music = Mix_LoadMUS("assests/ObservingTheStar.ogg");
    app.shot = Mix_LoadWAV("assests/sfx_laser2.ogg");
    Mix_PlayMusic(app.music, -1);

    SDL_Texture* title = loadTexture("assests/title.png");
    SDL_Texture* bgImg = loadTexture("assests/space-2.png");
    SDL_Texture* health = loadTexture("assests/heart.png");
    SDL_Texture* life = loadTexture("assests/playerLife2_blue.png");
    SDL_Texture* green = loadTexture("assests/green.png");
    SDL_Texture* over = loadTexture("assests/gameOver.png");
	
    atexit(cleanup);
	
    while (1)
    {
        switch(app.screen)
        {
            case MENU_SCREEN: 
                prepareScene();
                doInput();
                gameMenu(bgImg, title);
                presentScene();
                SDL_Delay(16);
                break;
            case GAME_SCREEN:
                prepareScene();
                doInput();
                handleMovement();
                update(bgImg, health, life, green);
                collisions();
                presentScene();
                SDL_Delay(16);
                break;
            case FREEZE_SCREEN: 
                prepareScene();
                doInput();
                checkPlay(2);
                update(bgImg, health, life, green);
                prepareScene();
                SDL_Delay(16);
                break;
            case DEATH_SCREEN: 
                prepareScene();
                doInput();
                checkPlay(3);
                scoreScreen(over);
                presentScene();
                SDL_Delay(16);
                break;
        }
    }

    return 0;
}
