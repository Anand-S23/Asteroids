// Includes 
#include "main.h"

// Definitions
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

void initGame()
{
     player.x = SCREEN_WIDTH / 2;
     player.y = (3 * SCREEN_HEIGHT) / 4;
     player.angle = -90.0;
     player.health = 100; 
     player.texture = loadTexture("assests/player.png");

}

void handleMovement()
{
	// Player movement 
	if (app.up)
	{
       	player.y -= 4;
	}
	if (app.down)
	{
       	player.y += 4;
	}
	if (app.right)
	{
	    player.x += 4; 
	}
	if (app.left)
	{
	    player.x -= 4;
	}
}

void update()
{
    blitRotated(player.texture, player.x, player.y, player.angle);
}

// Main Loop 
int main(int argc, char* argv)
{
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));
    
    CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
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
