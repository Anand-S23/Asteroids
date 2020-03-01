#include "math.h"

int randRange(int start, int end)
{
    srand(time(NULL));
    return (rand() % (end - start + 1));
}