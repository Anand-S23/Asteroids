// Includes 
#include "common.h"

// Definitions
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

App app;
Entity player;


// Main Loop 
int main(int argc, char* argv)
{
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));
    
    CreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

    player.x = 100;
    player.y = 100;
    player.texture = loadTexture("assests/player.png");
	
    atexit(cleanup);
	
    while (1)
    {
        prepareScene();
	doInput();

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

	blit(player.texture, player.x, player.y);
        presentScene();		
	SDL_Delay(16);
    }

    return 0;
}
