#include <genesis.h>
#include "minigame.h"

static void Menu_Draw(void)
{
    VDP_clearText(4, 12, 32);
    VDP_clearText(4, 13, 32);
    VDP_clearText(4, 14, 32);

    VDP_drawText("Press A to play pong", 12, 12);
    VDP_drawText("Press B to play tetris", 12, 13);
    VDP_drawText("Press C to play pang", 12, 14);
}

static void Menu_PlayMinigame(const minigameId id)
{
    Minigame_GetById(id)->run();
    Menu_Draw();
}

int main(bool hardReset)
{
    Menu_Draw();

    while (1)
    {
        u16 joy_state = JOY_readJoypad(JOY_1);

        if (joy_state & BUTTON_A)
            Menu_PlayMinigame(Pong);
        if (joy_state & BUTTON_B)
            Menu_PlayMinigame(Tetris);
        if (joy_state & BUTTON_C)
            Menu_PlayMinigame(Pang);

        SYS_doVBlankProcess();
    }

    return 0;
}
