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

void blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRotated(SDL_Texture* texture, int x, int y, int angle)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    dest.x -= (dest.w / 2);
    dest.y -= (dest.h / 2);

    SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}