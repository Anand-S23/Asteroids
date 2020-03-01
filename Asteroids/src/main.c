// Includes 
#include "main.h"

void initGame()
{
    CreateWindow("Asteroids", SCREEN_WIDTH, SCREEN_HEIGHT);
    player.x = SCREEN_WIDTH / 2;
    player.y = (3 * SCREEN_HEIGHT) / 4;
    player.angle = -90.0;
    player.health = 100; 
    player.texture = loadTexture("assests/player.png");
     
    createAsteroid(asteroids, 1);
}

void handleMovement()
{
	// Player movement 
	if (app.up)
	{
       	player.y -= 4.0;
	}
	if (app.down)
	{
       	player.y += 4.0;
	}
	if (app.right)
	{
	    player.x += 4.0; 
	}
	if (app.left)
	{
	    player.x -= 4.0;
	}

	//loop through to update the Asteroids
    for (int i = 0; i < MAX_AST; ++i)
    {
        if (asteroids[i])
        {
            asteroids[i]->angle += 0.9;
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
