#include "asteroid.h"

// Asteroid
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
        ast[pos]->dx = randDouble(-5, 5);
        ast[pos]->dy = randDouble(-5, 5);
        ast[pos]->size = size;
        if (size == 2)
        { 
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_big1.png");
        }
        if (size == 1)
        {
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_med1.png");
        }
        if (size == 0)
        {
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_small1.png");
        }
        ast[pos]->angle = 90.0 + randDouble(0, 360); 

        //printf("[Created]::(%lf,%lf)-(%lf,%lf)-%d-%d-%lf\n", ast[pos]->x, ast[pos]->y, ast[pos]->dx, ast[pos]->dy, ast[pos]->size, ast[pos]->angle);
    }
}

void placeAsteroid(Asteroid* ast[], double x, double y, int size)
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

        ast[pos]->x = x;  
        ast[pos]->y = y;
        ast[pos]->dx = randDouble(-5, 5);
        ast[pos]->dy = randDouble(-5, 5);
        ast[pos]->size = size;
        if (size == 2)
        { 
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_big1.png");
        }
        if (size == 1)
        {
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_med1.png");
        }
        if (size == 0)
        {
            ast[pos]->texture = loadTexture("assests/Meteors/meteorGrey_small1.png");
        }
        ast[pos]->angle = 90.0 + randDouble(0, 360);
    }        
}

void destroyAsteroid(Asteroid* ast[], int pos)
{
    free(ast[pos]);
    ast[pos] = NULL;
}

// Bullets 
void createBullet(Bullet* bullets[], double  x, double y, double angle)
{
    int pos = -1;
    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        if (bullets[i] == NULL)
        {
            pos = i;
            break;
        }
    }

    if (pos >= 0)
    {
        bullets[pos] = malloc(sizeof(Bullet));
        bullets[pos]->x = x; 
        bullets[pos]->y = y; 
        bullets[pos]->angle = angle; 
        bullets[pos]->texture = loadTexture("assests/laser.png");
    }
}

void destroyBullet(Bullet* bullets[], int pos)
{
    free(bullets[pos]);
    bullets[pos] = NULL;
}

// checks bullet and asteroid collisions 
int bulletCollision(Asteroid* ast, Bullet* bullet)
{
    SDL_Rect a, b;

    SDL_QueryTexture(ast->texture, NULL, NULL, &a.w, &a.h);
    SDL_QueryTexture(bullet->texture, NULL, NULL, &b.w, &b.h);

    double aTop = ast->y - a.h;
    double aBot = ast->y + a.h;
    double aLeft = ast->x - a.w;
    double aRight = ast->x + a.w;
    double bTop = bullet->y - b.h;
    double bBot = bullet->y + b.h;
    double bLeft = bullet->x - b.w;
    double bRight = bullet->x + b.w;


    // if ((aTop < bTop && aBot > bTop) || (aTop < bBot && aBot > bBot))
    // {
    //     if ((aLeft <= bLeft && aRight >= bLeft) || (aLeft <= bRight && aLeft >= bRight))
    //     {
    //         return 1;
    //     }
    // }

    return 1;
}

// checks asteroid and player collisons
int playerCollision(Asteroid* ast, Entity player)
{
    SDL_Rect a, p;

    SDL_QueryTexture(ast->texture, NULL, NULL, &a.w, &a.h);
    SDL_QueryTexture(player.texture, NULL, NULL, &p.w, &p.h);

    // (green, player.x - (a.w/2 - 35), player.y, a.w - 70, a.h);
    double aTop = ast->y - a.h;
    double aBot = ast->y + a.h;
    double aLeft = ast->x - a.w;
    double aRight = ast->x + a.w;
    double pTop = player.y;
    double pBot = player.y + p.h;
    double pLeft = player.x - (p.w/2 - 35);
    double pRight = player.x + (p.w/2 + 35);

    if ((aTop < pTop && aBot > pTop) || (aTop < pBot && aBot > pBot))
    {
        if ((aLeft <= pLeft && aRight >= pLeft) || (aLeft <= pRight && aLeft >= pRight))
        {
            return 1;
        }
    }

    return 0;
}