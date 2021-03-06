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
extern void placeAsteroid(Asteroid* ast[], double x, double y, int size);
extern void createBullet(Bullet* bullets[], double x, double y, double angle);
extern void destroyAsteroid(Asteroid* ast[], int pos);
extern void destroyBullet(Bullet* bullets[], int pos);
extern int randRange(int start, int end);
extern int bulletCollision(Asteroid* ast, Bullet* bullet);
extern int playerCollision(Asteroid* ast, Entity player);
extern void sortScores(int* scores); 
extern void addScore(int score);
extern void scoreLogger(int* scores);
extern void readScores(int* scores);
extern SDL_Texture* showScore(SDL_Color textColor, int score);

App app;
Entity player;

Asteroid* asteroids[MAX_AST] = { NULL };
Bullet* bullets [MAX_BULLETS] = { NULL };
