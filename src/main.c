#include "genesis.h"
#include "minigame.h"


void Menu_Draw(void) {
    VDP_clearText(4, 12, 32);
    VDP_clearText(4, 13, 32);
    VDP_clearText(4, 14, 32);

    VDP_drawText("Press A to play pong", 12, 12);
    VDP_drawText("Press B to play tetris", 12, 13);
    VDP_drawText("Press C to play pang", 12, 14);
}

void Menu_PlayMinigame(char *id) {
    struct minigame *current_minigame;

    current_minigame = Minigame_GetById(id);
    current_minigame->run();
    Menu_Draw();
}

int main(bool hardReset) {
    u16 joy_state;

    Menu_Draw();

    while (1) {
        joy_state = JOY_readJoypad(JOY_1);

        if (joy_state & BUTTON_A) Menu_PlayMinigame("pong");
        if (joy_state & BUTTON_B) Menu_PlayMinigame("tetris");
        if (joy_state & BUTTON_C) Menu_PlayMinigame("pang");

        SYS_doVBlankProcess();
    }

    return 0;
}
