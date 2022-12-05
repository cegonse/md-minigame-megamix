#include "menu.h"
#include "common.h"

#define SCROLL_MAX_OFFSET FIX16(32)
#define SCROLL_STEP FIX16(0.4)

static f16 bgHorizontalScroll = 0;
static f16 bgVerticalScroll = 0;

static void scrollGameBackground()
{
    VDP_setHorizontalScroll(BG_B, fix16ToRoundedInt(bgHorizontalScroll));
    VDP_setVerticalScroll(BG_B, fix16ToRoundedInt(bgVerticalScroll));

    bgHorizontalScroll = fix16Sub(bgHorizontalScroll, SCROLL_STEP);
    bgVerticalScroll = fix16Add(bgVerticalScroll, SCROLL_STEP);
    
    if(bgHorizontalScroll <= -SCROLL_MAX_OFFSET || bgVerticalScroll >= SCROLL_MAX_OFFSET)
    {
        bgHorizontalScroll = FIX16(0);
        bgVerticalScroll = FIX16(0);
    }
}

static void setupText()
{
    VDP_setTextPalette(PAL2);
    
    PAL_setColor(PAL2 * PALETTE_SIZE + TEXT_COLOR_INDEX, RGB8_8_8_TO_VDPCOLOR(0, 0, 0));

    VDP_drawText("2022", 1, 22);
    VDP_drawText("Code by Cyto", 1, 24);
    VDP_drawText("Graphics by XXXXX", 1, 25);
    VDP_drawText("Music/sound by XXXXX", 1, 26);
}

static u8 blinkingFrameCounter = 0;

static void blinkTexT()
{
    ++ blinkingFrameCounter;

    if(blinkingFrameCounter == 20)
    {
        VDP_clearText(10, 16, sizeof "PRESS START BUTTON");
    }
    else if(blinkingFrameCounter == 40)
    {
        VDP_drawText("PRESS START BUTTON", 10, 16);
        blinkingFrameCounter = 0;
    }
}

bool MDInvadersMenu()
{
    setAllPalettesToBlack();

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    VDP_drawImageEx(BG_B, &MenuBackground, TILE_ATTR_FULL(PAL0, 0, 0, 0, TILE_USERINDEX), 0, 0, FALSE, TRUE);
    VDP_drawImageEx(BG_A, &Title, TILE_ATTR_FULL(PAL1, 0, 0, 0, MenuBackground.tileset->numTile + TILE_USERINDEX), 0, 0, FALSE, TRUE);

    setupText();

    PAL_setPalette(PAL0, MenuBackground.palette->data, CPU);
    PAL_setPalette(PAL1, Title.palette->data, CPU);

    u16 lastJoyState = JOY_readJoypad(JOY_1);

    while(TRUE)
    {
        const u16 joyState = JOY_readJoypad(JOY_1);

        if((joyState & BUTTON_START) && !(lastJoyState & BUTTON_START))
        {
            break;
        }

        lastJoyState = joyState;

        scrollGameBackground();

        blinkTexT();

        SPR_update();

        VDP_showCPULoad();
        SYS_doVBlankProcess();
    }

    setAllPalettesToBlack();
    
    return FALSE;
}