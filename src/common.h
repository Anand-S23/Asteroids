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
#include "SDL_mixer.h"
#include "SDL_ttf.h"
 
// Definition 
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

#define MAX_AST 30
#define MAX_BULLETS 15
#define RAD 3.14159265/180.0

// Enums
enum screenState {
    MENU_SCREEN = 0,
    GAME_SCREEN = 1,
    FREEZE_SCREEN = 2, 
    DEATH_SCREEN = 3,
    test = 4,
};

// Structs
typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int up;
    int down;
    int right;
    int left;
    int space;
    int screen;
    int score;
    Mix_Music *music; 
    Mix_Chunk *shot; 
    TTF_Font *font;
    SDL_Surface *scoreDisplay;
} App;

typedef struct entity {
    double x, y;
    double angle;
    int lives;
    SDL_Texture *texture;
} Entity;

typedef struct{
    double x, y; 
    double angle; 
    double dx, dy;
    int size;
    SDL_Texture *texture;
} Asteroid;

typedef struct bullet{
    double x, y;
    double angle; 
    SDL_Texture *texture; 
} Bullet;

