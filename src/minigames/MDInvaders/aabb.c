#include "aabb.h"


void aabb_update(struct AABB* aabb, s16 newX, s16 newY, u16 width, u16 height)
{
    aabb->left = newX;
    aabb->top = newY;
    aabb->right = newX + width - 1;
    aabb->bottom = newY + height - 1;
}

boolean aabb_isPointInside(s16 x, s16 y, struct AABB* aabb)
{
    return x >= aabb->left && y >= aabb->top && x <= aabb->bottom && y <= aabb->right;
}

boolean aabb_areOverlapping(struct AABB* aabb1, struct AABB* aabb2)
{
    return aabb1->right >= aabb2->left && aabb2->right >= aabb1->left && 
            aabb1->bottom >= aabb2->top && aabb2->bottom >= aabb1->top;
}