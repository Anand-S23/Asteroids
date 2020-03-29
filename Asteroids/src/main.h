#include "common.h"

extern void cleanup(void);
extern void CreateWindow(char* name, int width, int height);
extern void prepareScene(void);
extern void presentScene(void);
extern void doInput(void);
extern void blit(SDL_Texture* texture, double x, double y);
extern void blitRotated(SDL_Texture* texture, double x, double y, double angle);
extern SDL_Texture* loadTexture(char* file);
extern void createAsteroid(Asteroid* ast[], int size);
extern int randRange(int start, int end);

App app;
Entity player;

Asteroid* asteroids[MAX_AST] = { NULL };
