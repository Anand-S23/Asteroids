#include <math.h>
#include <stdio.h>
#include <stdlib.h> 

int main()
{
    double w = 40.0;
    double h = 40.0;

    double c1 = atan2(-w, h);
    double c2 = atan2(w, h);
    double c3 = atan2(w, -h);
    double c4 = atan2(-w, -h);

    printf("c1 = %lf, c2 = %lf, c3 = %lf, c4 = %lf\n", c1, c2, c3, c4);

    return 0; 
}