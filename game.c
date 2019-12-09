// Main Game FIle
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    // Window rendering to
    SDL_Window* window = NULL;

    // Surface contained by the window
    SDL_Surface* screenSurface = NULL;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("SDL could not initalize. SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create Window
	window = SDL_CreateWindow("Game", 
			          SDL_WINDOWPOS_UNDEFINED, 
				  SDL_WINDOWPOS_UNDEFINED,
				  SCREEN_WIDTH, SCREEN_HEIGHT,
				  SDL_WINDOW_SHOWN);
	if(window == NULL) 
	{
             printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
	}
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
