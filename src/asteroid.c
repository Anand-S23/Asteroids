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

    double aTop = ast->y - (a.h / 2) + 10;
    double aBot = ast->y + (a.h / 2) - 10;
    double aLeft = ast->x - (a.w / 2) + 10;
    double aRight = ast->x + (a.w / 2) - 10;
    double bTop = bullet->y - (b.h / 2);
    double bBot = bullet->y + (b.h / 2);
    double bLeft = bullet->x - (b.w / 2);
    double bRight = bullet->x + (b.w / 2);

    // vertex -> (x, y) = (bLeft, bTop) - (bRight, bTop) - (bLeft, bBot) - (bRight, bBot)
    // x' = x*cos(t) - y*sin(t)
    // y' = x*sin(t) + y*cos(t)
    double c1x = bLeft*cos(bullet->angle*RAD) - bTop*sin(bullet->angle*RAD); 
    double c1y = bLeft*sin(bullet->angle*RAD) + bTop*cos(bullet->angle*RAD); 

    double c2x = bRight*cos(bullet->angle*RAD) - bTop*sin(bullet->angle*RAD); 
    double c2y = bRight*sin(bullet->angle*RAD) + bTop*cos(bullet->angle*RAD); 

    double c3x = bLeft*cos(bullet->angle*RAD) - bBot*sin(bullet->angle*RAD); 
    double c3y = bLeft*sin(bullet->angle*RAD) + bBot*cos(bullet->angle*RAD); 

    double c4x = bRight*cos(bullet->angle*RAD) - bBot*sin(bullet->angle*RAD); 
    double c4y = bRight*sin(bullet->angle*RAD) + bBot*cos(bullet->angle*RAD); 

    SDL_RenderDrawPoint(app.renderer, c1x, c1y);
    SDL_RenderDrawPoint(app.renderer, c2x, c2y);
    SDL_RenderDrawPoint(app.renderer, c3x, c3y);
    SDL_RenderDrawPoint(app.renderer, c4x, c4y);

    if ((aTop < c1y && aBot > c1y) && (aLeft < c1x && aRight > c1x))
    {
        return 1;
    }
    else if ((aTop < c2y && aBot > c2y) && (aLeft < c2x && aRight > c2x))
    {
        return 1; 
    }
    else if ((aTop < c3y && aBot > c3y) && (aLeft < c3x && aRight > c3x))
    {
        return 1; 
    }
    else if ((aTop < c4y && aBot > c4y) && (aLeft < c4x && aRight > c4x))
    {
        return 1; 
    }


    return 0;
}

// checks asteroid and player collisons
int playerCollision(Asteroid* ast, Entity player)
{
    SDL_Rect a, p;

    SDL_QueryTexture(ast->texture, NULL, NULL, &a.w, &a.h);
    SDL_QueryTexture(player.texture, NULL, NULL, &p.w, &p.h);

    double aTop = ast->y - (a.h / 2) + 10;
    double aBot = ast->y + (a.h / 2) - 10;
    double aLeft = ast->x - (a.w / 2) + 10;
    double aRight = ast->x + (a.w / 2) - 10;
    double pTop = player.y;
    double pBot = player.y + p.h;
    double pLeft = player.x - (p.w/2 - 35);
    double pRight = player.x + (p.w/2);

    double c1x = pLeft*cos(player.angle*RAD) - pTop*sin(player.angle*RAD); 
    double c1y = pLeft*sin(player.angle*RAD) + pTop*cos(player.angle*RAD); 

    double c2x = pRight*cos(player.angle*RAD) - pTop*sin(player.angle*RAD); 
    double c2y = pRight*sin(player.angle*RAD) + pTop*cos(player.angle*RAD); 

    double c3x = pLeft*cos(player.angle*RAD) - pBot*sin(player.angle*RAD); 
    double c3y = pLeft*sin(player.angle*RAD) + pBot*cos(player.angle*RAD); 

    double c4x = pRight*cos(player.angle*RAD) - pBot*sin(player.angle*RAD); 
    double c4y = pRight*sin(player.angle*RAD) + pBot*cos(player.angle*RAD);

    //SDL_Rect rect = {pLeft, pTop, (p.w - 70), p.h};
    //SDL_RenderDrawRect(app.renderer, &rect);

    SDL_RenderDrawPoint(app.renderer, c1x, c1y);
    SDL_RenderDrawPoint(app.renderer, c2x, c2y);
    SDL_RenderDrawPoint(app.renderer, c3x, c3y);
    SDL_RenderDrawPoint(app.renderer, c4x, c4y);

    if ((aTop < c1y && aBot > c1y) && (aLeft < c1x && aRight > c1x))
    {
        return 0;
    }
    else if ((aTop < c2y && aBot > c2y) && (aLeft < c2x && aRight > c2x))
    {
        return 0; 
    }
    else if ((aTop < c3y && aBot > c3y) && (aLeft < c3x && aRight > c3x))
    {
        return 0; 
    }
    else if ((aTop < c4y && aBot > c4y) && (aLeft < c4x && aRight > c4x))
    {
        return 0; 
    }

    return 0;
}

// Hi-Score 
void sortScores(int* scores)
{
    for (int i = 0; i < 6; ++i)
    {
        int key = scores[i];
        int pos = i - 1;

        while(pos >= 0 && scores[pos] > key)
        {
            scores[pos+1] = scores[pos];
            pos -= 1;
        }
    }
}

void scoreLogger(int* scores)
{
	FILE* input = fopen("scores.dat", "w");
	if (input == NULL)
	{
		printf("Could not open file");
		return;
	}

	for (int i = 0; i < 5; ++i)
    {
        fprintf(input,"%d", scores[i]);
    }
	
	fclose(input);
}

void addScore(int score)
{
    int num;
    int scores[6];
    FILE* input = fopen("scores.dat", "r");
	if (input == NULL)
	{
		printf("Could not open file");
		return;
	}

    for (int i = 0; i < 5; ++i)
    {
        fscanf(input, "%d", &num);
        scores[i] = num;
    }

    scores[5] = score;
    sortScores(scores);
	scoreLogger(scores);
	fclose(input);
}

