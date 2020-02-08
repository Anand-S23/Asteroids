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
    int x;
    int y;
    double angle;
    SDL_Texture *texture;
} Entity;