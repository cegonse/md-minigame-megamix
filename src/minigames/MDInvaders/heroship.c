#include "heroship.h"
#include "common.h"

#define HERO_SHIP_Y 195
#define HERO_SHIP_SPEED 2
#define HERO_SHIP_LEFT_BOUND 0
#define HERO_SHIP_RIGHT_BOUND 296

static Sprite* sprite;
static s16 x;

void setupHeroShip()
{
    PAL_setPalette(PAL2, HeroShip.palette->data, CPU);

    x = screenWidth / 2 - HeroShip.w / 2;

    sprite = SPR_addSprite(&HeroShip, x, HERO_SHIP_Y, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
}

void updateHeroShip()
{
    const u16 joyState = JOY_readJoypad(JOY_1);

    if(joyState & BUTTON_LEFT && x > HERO_SHIP_LEFT_BOUND)
    {
        x -= HERO_SHIP_SPEED;
    }
    else if(joyState & BUTTON_RIGHT && x < HERO_SHIP_RIGHT_BOUND)
    {
        x += HERO_SHIP_SPEED;
    }

    SPR_setPosition(sprite, x, HERO_SHIP_Y);

    if(joyState & BUTTON_B)
    {
    }

    // char buffer[24];
    // sprintf(buffer, "%d", x);
    // VDP_clearText(0, 0, 10);
    // VDP_drawText(buffer, 0, 0);
}

void clearHeroShip()
{
    SPR_releaseSprite(sprite);
}