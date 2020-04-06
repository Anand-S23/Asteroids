#include "common.h"

extern void cleanup(void);
extern void CreateWindow(char* name, int width, int height);
extern void prepareScene(void);
extern void presentScene(void);
extern void doInput(void);
extern void blit(SDL_Texture* texture, int x, int y, int width, int height);
extern void blitRotated(SDL_Texture* texture, double x, double y, double angle);
extern void blitPlayer(SDL_Texture* texture, double x, double y, double angle);
extern void rect(int x, int y, int w, int h, int r, int g, int b);
extern SDL_Texture* loadTexture(char* file);
extern void createAsteroid(Asteroid* ast[], int size);
extern void createBullet(Bullet* bullets[], double x, double y, double angle);
extern void destroyAsteroid(Asteroid* ast[], int pos);
extern void destroyBullet(Bullet* bullets[], int pos);
extern int randRange(int start, int end);
extern int bulletCollision(Asteroid* ast, Bullet* bullet);

App app;
Entity player;

Asteroid* asteroids[MAX_AST] = { NULL };
Bullet* bullets [MAX_BULLETS] = { NULL };
