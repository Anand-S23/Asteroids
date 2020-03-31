#include "math.h"

int randInt(int start, int end)
{
    return ((rand() % (end - start + 1)) + start);
}

double randDouble(int start, int end)
{ 
    return (double)((rand() % (end - start + 1)) + start);
}