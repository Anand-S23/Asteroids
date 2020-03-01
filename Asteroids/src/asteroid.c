#include "asteroid.h"

void createAsteroid(Asteroid* ast[], int size)
{
    int pos = -1;
    for (int i = 0; i < MAX_AST; ++i)
    {
        if (ast[i] == NULL)
        {
            pos = i; 
            break;
        }
    }

    if (pos >= 0)
    {
        ast[pos] = malloc(sizeof(Asteroid));

        ast[pos]->x = (double) randRange(0, SCREEN_WIDTH);  
        ast[pos]->y = (double) randRange(0, SCREEN_HEIGHT); 
        ast[pos]->size = size;
        if (size == 2)
        {
            ast[pos]->health = 25; 
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_big1.png");
        }
        if (size == 1)
        {
            ast[pos]->health = 15; 
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_big1.png");
        }
        if (size == 0)
        {
            ast[pos]->health = 10;
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_big1.png");
        }
        ast[pos]->angle = 90.0 + (double) randRange(0, 360); 
    }
}

void destroyAsteroid(Asteroid* ast[], int pos)
{
    free(ast[pos]);
    ast[pos] = NULL;
}