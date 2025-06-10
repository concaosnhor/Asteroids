#include "utils.h"

bool isCollide(Entity* a, Entity* b)
{
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float distSq = dx * dx + dy * dy;
    float radiusSum = a->R + b->R;
    return distSq < radiusSum * radiusSum;
}
