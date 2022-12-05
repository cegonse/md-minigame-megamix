#include "game.h"
#include "common.h"
#include "gamebackground.h"
#include "heroship.h"

static void clear();

bool MDInvadersGame()
{
    setAllPalettesToBlack();

    setupGameBackground();
    setupHeroShip();

    VDP_setTextPalette(PAL3);

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
        updateHeroShip();

        SPR_update();

        VDP_showCPULoad();
        SYS_doVBlankProcess();
    }

    clear();
    
    return FALSE;
}

static void clear()
{
    clearHeroShip();
}