#include "genesis.h"

void Pang_Main(void)
{
    u16 joy_state;

    VDP_clearText(4, 12, 32);
    VDP_clearText(4, 13, 32);
    VDP_clearText(4, 14, 32);

    VDP_drawText("Running pang minigame!!", 4, 12);
    VDP_drawText("Press START to go back to menu", 4, 13);

    while (1) {
        joy_state = JOY_readJoypad(JOY_1);

        if (joy_state & BUTTON_START) {
            return;
        }

        SYS_doVBlankProcess();
    }
}
