#pragma once

#include <genesis.h>

typedef u8 boolean;

struct AABB
{
    s16 left;
    s16 top;
    u16 right;
    u16 bottom;
};

void aabb_update(struct AABB* aabb, s16 newX, s16 newY, u16 width, u16 height);

boolean aabb_isPointInside(s16 x, s16 y, struct AABB* aabb);
boolean aabb_areOverlapping(struct AABB* aabb1, struct AABB* aabb2);