#include "ast_platform.h"

// ----- INITIALIZING ----- // 
// Initialize SDL + Create window
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
    
    app.window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDLWINDOWPOS_UNDEFINED,
                                  screenWidth, screenHeight, windowFlags);
    
    if (!app.window)
    {
        printf("Failed to open %d x %d window: %s\n", 
               screenWidth, screenHeight, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if (!app.renderer)
    {
        printf("Failed to create renderer: %sn", SDL_GetError());
        exit(1);
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    TTF_Init();
}

// Clean up before exiting
void cleanup(void)
{
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWIndow(app.window); 
    TTF_Quit();
    SDL_Quit();
}

// ----- RENDERING ----- //
void prepareScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
    SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
    SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename)
{
    SDL_Texture *texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    texture = IMG_LoadTexture(app.renderer, filename);
    if (texture == NULL)
    {
        printf("%s\n", SDL_GetError());
    }

    return texture;
}

void blit(SDL_Texture* texture, int x, int y, int width, int height)
{
    SDL_Rect dstrect = { x, y, width, height };
    SDL_RenderCopy(app.renderer, texture, NULL, &dstrect);
}

void blitRotated(SDL_Texture* texture, double x, double y, double angle)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x -= (dest.w / 2);
    dest.y -= (dest.h / 2);

    SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

void blitPlayer(SDL_Texture* texture, double x, double y, double angle)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x -= (dest.w / 2);
    dest.y -= 0;

    SDL_Point rotate = {dest.w/2, 0};

    SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, &rotate, SDL_FLIP_NONE);
}

void rect(int x, int y, int w, int h, int r, int g, int b)
{
    SDL_Rect rect = {x, y, w, h};

    SDL_SetRenderDrawColor(app.renderer, r, g, b, 255);
    SDL_RenderDrawRect(app.renderer, &rect);
    SDL_RenderFillRect(app.renderer, &rect);

    SDL_RenderPresent(app.renderer);
}

// ----- INPUT ----- //
void handleKeyDown(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0)
    {
        if ( event->keysym.scancode == SDL_SCANCODE_UP)
        {
            input.up = 1;
        }
        if ( event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            input.down = 1;
        }
        if ( event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            input.right = 1;
        }
        if ( event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            input.left = 1;
        }
        if ( event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
            input.space = 1;
        }
    }
}

void handleKeyUp(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0)
    {
        if ( event->keysym.scancode == SDL_SCANCODE_UP)
        {
            input.up = 0;
        }
        if ( event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            input.down = 0;
        }
        if ( event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            input.right = 0;
        }
        if ( event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            input.left = 0;
        }
        if ( event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
            input.space = 0;
        }
    }
}

void handleInput(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                exit(0);
            } break;

            case SDL_KEYDOWN:
            {
                handleKeyDown(&event.key);
            } break;

            case SDL_KEYUP:
            {
                handleKeyUp(&event.key); 
            } break;

            default: 
            {
                break;
            }
        }
    }
}