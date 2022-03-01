#include "stdio.h"

void main()
{
    float a = -1.234;
    int b = *((int*) &a);
    printf ("%X",b);
}