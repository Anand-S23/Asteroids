// Standard Libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// SDL2
#include "SDL.h"
#include "SDL_image.h"
 
// Structs
typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int up;
    int down;
    int right;
    int left;
} App;

typedef struct {
    double x;
    double y;
    double angle;
    int health;
    SDL_Texture *texture;
} Entity;

typedef struct {
    double x; 
    double y; 
    double angle; 
    int size;
    int health;
    SDL_Texture *texture;
} Asteriod;