// Includes 
#include "main.h"

// Definitions
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

int randRange(int start, int end, int neg)
{
    int retNum = (rand() % (end + 1 - start) + start);
     if (neg == 1)
     {
         int n = rand() % 2;
	 retNum = (n % 2 == 0) ? retNum : -retNum;
     }
     return (rand() % (end + 1 - start) + end);
}

Asteriod createAsteriod(int size)
{
    Asteriod retAst;
    retAst.x = randRange(0, SCREEN_WIDTH, 0); 
    retAst.y = randRange(0, SCREEN_HEIGHT, 0);
    if (retAst.size == 2)
    {
         retAst.health = 25; 
 	 retAst.texture = loadTexture("assests/Meteors/meteorGrey_big1.png");
    }
    if (retAst.size == 1)
    {
        retAst.health = 15; 
    }
    if (retAst.size == 0)
    {
        retAst.health = 10;
    }
    retAst.angle = randRange(0, 180, 1);

    return retAst;
}

void initGame()
{
     CreateWindow("Asteriods", SCREEN_WIDTH, SCREEN_HEIGHT);
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

void update(Asteriod ast)
{
    blitRotated(player.texture, player.x, player.y, player.angle);
    blitRotated(ast.texture, ast.x, ast.y, ast.angle);
}

// Main Loop 
int main(int argc, char* argv)
{
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));
    Asteriod asteriods[100];
    Asteriod ast = createAsteriod(1);

    initGame();
	
    atexit(cleanup);
	
    while (1)
    {
        prepareScene();
		doInput();
		handleMovement();
		update(ast);
		presentScene();
		SDL_Delay(16);
    }

    return 0;
}
