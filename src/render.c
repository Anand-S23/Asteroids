#include "render.h"

// Darwing
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