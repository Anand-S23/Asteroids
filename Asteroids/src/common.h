// Standard Libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h> 

// SDL2
#include "SDL.h"
#include "SDL_image.h"
 
// Definition 
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

#define MAX_AST 1000
#define RAD 3.14159265/180.0

// Structs
typedef struct{
    SDL_Renderer *renderer;
    SDL_Window *window;
    int up;
    int down;
    int right;
    int left;
} App;

typedef struct{
    double x, y;
    double angle;
    int health;
    SDL_Texture *texture;
} Entity;

typedef struct{
    double x, y; 
    double angle; 
    double dx, dy;
    int size;
    int health;
    SDL_Texture *texture;
} Asteroid;

/*
typedef struct bullet{
    double x, y;
    double angle; 
    int health; 
    SDL_Texture *texture; 
} Bullet;
*/
