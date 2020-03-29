// Includes 
#include "main.h"

void initGame()
{
    srand(time(NULL));

    CreateWindow("Asteroids", SCREEN_WIDTH, SCREEN_HEIGHT);
    player.x = SCREEN_WIDTH / 2;
    player.y = (3 * SCREEN_HEIGHT) / 4;
    player.angle = -90.0;
    player.health = 100; 
    player.texture = loadTexture("assests/player.png");

    for (int i = 0; i < 8; ++i) 
    {
        int size = randInt(1, 2);
        createAsteroid(asteroids, size);
        //printf("Pos: %d, Size: %d\n", i, size);
    }

    for (int i = 0; i < 2; ++i)
        createAsteroid(asteroids, 0);
}

void handleMovement()
{
	// Player movement 
	if (app.up)
    {
       	player.y += 4.0*sin(player.angle*RAD);
        player.x += 4.0*cos(player.angle*RAD);
    }
	if (app.right)
	    player.angle += 1.0; 
	if (app.left)
	    player.angle -= 1.0;

    if (player.angle < -180.0)
        player.angle = 180.0;
    if (player.angle > 180.0)
        player.angle = -180.0; 


    if (player.x < 0.0)
        player.x = SCREEN_WIDTH;
    if (player.x > SCREEN_WIDTH)
        player.x = 270.0;
    if (player.y < 0.0)
        player.y = SCREEN_HEIGHT;
    if (player.y > SCREEN_HEIGHT)
        player.y = 0.0;

	//loop through to update the Asteroids
    for (int i = 0; i < MAX_AST; ++i)
    {
        if (asteroids[i])
        {
            asteroids[i]->angle += 0.9;
            asteroids[i]->x += asteroids[i]->dx;
            asteroids[i]->y += asteroids[i]->dy;
            //printf("%lf %lf\n", asteroids[i]->x, asteroids[i]->y);
            if (asteroids[i]->dx < 0 && asteroids[i]->x < 0)
                asteroids[i]->x = (double) SCREEN_WIDTH;
            if (asteroids[i]->dx > 0 && asteroids[i]->x > SCREEN_WIDTH)
                asteroids[i]->x = 0.0;
            if (asteroids[i]->dy < 0 && asteroids[i]->y < 0)
                asteroids[i]->y = (double) SCREEN_HEIGHT;
            if (asteroids[i]->dy > 0 && asteroids[i]->y > SCREEN_HEIGHT)
                asteroids[i]->y = 0.0;
        }
    }
}

void update()
{
    blitRotated(player.texture, player.x, player.y, player.angle);

    // loop through the list of Asteroid and blit
    for (int i = 0; i < MAX_AST; ++i)
    {
        if (asteroids[i])
        {
            blitRotated(asteroids[i]->texture, asteroids[i]->x, asteroids[i]->y, asteroids[i]->angle);
        }
    }
}

// Main Loop 
int main(int argc, char* argv)
{
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));

    initGame();
	
    atexit(cleanup);
	
    while (1)
    {
        prepareScene();
		doInput();
		handleMovement();
		update();
		presentScene();
		SDL_Delay(16);
    }

    return 0;
}