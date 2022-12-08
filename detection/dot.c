#include "dot.h"
#include <stdlib.h>

struct dot* init_dot(int x, int y)
{
    struct dot* res =malloc(sizeof(struct dot));
    res->x= x;
    res->y = y;
    return res;
}

