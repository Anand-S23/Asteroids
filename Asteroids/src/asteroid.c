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

        ast[pos]->x = randDouble(200, SCREEN_WIDTH - 200);  
        ast[pos]->y = randDouble(200, SCREEN_HEIGHT - 200); 
        ast[pos]->dx = randDouble(-5, 8);
        ast[pos]->dy = randDouble(-5, 8);
        ast[pos]->size = size;
        if (size == 2)
        {
            ast[pos]->health = 25; 
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_big1.png");
        }
        if (size == 1)
        {
            ast[pos]->health = 15; 
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_med1.png");
        }
        if (size == 0)
        {
            ast[pos]->health = 10;
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_small1.png");
        }
        ast[pos]->angle = 90.0 + randDouble(0, 360); 

        printf("[Created]::(%lf,%lf)-(%lf,%lf)-%d-%d-%lf\n", ast[pos]->x, ast[pos]->y, ast[pos]->dx, ast[pos]->dy, ast[pos]->size, ast[pos]->health, ast[pos]->angle);
    }
}

void destroyAsteroid(Asteroid* ast[], int pos)
{
    free(ast[pos]);
    ast[pos] = NULL;
}