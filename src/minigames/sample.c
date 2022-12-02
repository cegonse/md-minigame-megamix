#include "genesis.h"

void Sample_Main(void)
{
    u16 joy_state;

    VDP_drawText("use this as your minigame sample", 4, 12);

    while (1) {
        joy_state = JOY_readJoypad(JOY_1);

        if (joy_state & BUTTON_START) {
            return;
        }

        SYS_doVBlankProcess();
    }
}
