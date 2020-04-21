#include "initalize.h"

// Starts up SDL
void CreateWindow(char* name, int screenWidth, int screenHeight)
{
	int rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, windowFlags);
	
	if (!app.window)
	{
		printf("Failed to open %d x %d window: %s\n", screenWidth, screenHeight, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);
	
	if (!app.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	TTF_Init();
	//if (!TTF_Init())
	//	printf("%s\n", SDL_GetError());
}

// Cleans up before exiting
void cleanup(void)
{
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	TTF_Quit();
	SDL_Quit();
}
