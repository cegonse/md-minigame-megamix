#include "gamebackground.h"
#include "common.h"

#define CLOUD_STRIP_NUMBER 5
#define STATIC_STRIP_TILES 20

const f16 StripSpeeds[CLOUD_STRIP_NUMBER] = {FIX16(0.5), FIX16(0.4), FIX16(0.3), FIX16(0.2), FIX16(0.1)};

s16 stripValues1[2] = {0};
s16 stripValues2[2] = {0};
s16 stripValues3[2] = {0};
s16 stripValues4[1] = {0};
s16 stripValues5[1] = {0};

struct ScrollStrip
{
    f16 offset;
    u16 startTile;
    u16 tileNumber;
    s16* offsetValues;
};

struct ScrollStrip scrollStrips[CLOUD_STRIP_NUMBER] = 
{
    {FIX16(0), 0, 2, stripValues1},
    {FIX16(0), 2, 2, stripValues2},
    {FIX16(0), 4, 2, stripValues3},
    {FIX16(0), 6, 1, stripValues4},
    {FIX16(0), 7, 1, stripValues5}
};

void setupGameBackground()
{
    VDP_setHorizontalScroll(BG_B, 0);
    VDP_setVerticalScroll(BG_B, 0);

    VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);

    VDP_drawImageEx(BG_B, &GameBackground, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USERINDEX), 0, 0, TRUE, TRUE);

    VDP_clearPlane(BG_A, TRUE);
}

void scrollGameBackground()
{
    for(u16 i = 0; i < CLOUD_STRIP_NUMBER; ++ i)
    {
        scrollStrips[i].offset += StripSpeeds[i];
        
        memsetU16((u16*)scrollStrips[i].offsetValues, fix16ToInt(scrollStrips[i].offset), scrollStrips[i].tileNumber);
        
        VDP_setHorizontalScrollTile(BG_B, scrollStrips[i].startTile, scrollStrips[i].offsetValues, scrollStrips[i].tileNumber, DMA);
    }
}