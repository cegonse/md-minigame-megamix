#include <genesis.h>
#include "minigame.h"

static Minigame_t *minigames;
static u8 selected_minigame_index;
static u8 num_minigames;

static void Menu_Draw(void)
{
    VDP_clearText(2, 2, 32);
    VDP_clearText(2, 3, 32);

    VDP_drawText("Left, right: select minigame", 2, 2);
    VDP_drawText("Start: play", 2, 3);
}

static void Menu_DrawTitle(void)
{
    VDP_clearText(2, 10, 32);
    VDP_drawText(minigames[selected_minigame_index].title, 2, 10);
}

static void Menu_PlayMinigame(void)
{
    minigames[selected_minigame_index].run();
    Menu_Draw();
    Menu_DrawTitle();
}

int main(bool hardReset)
{
    u16 last_joy_state = 0;

    minigames = Minigame_GetAll();
    num_minigames = Minigame_Count();
    selected_minigame_index = 0;

    Menu_Draw();
    Menu_DrawTitle();

    while (1)
    {
        u16 joy_state = JOY_readJoypad(JOY_1);

        if (joy_state & BUTTON_RIGHT && !(last_joy_state & BUTTON_RIGHT)) {
            selected_minigame_index++;

            if (selected_minigame_index == num_minigames) {
                selected_minigame_index = 0;
            }

            Menu_DrawTitle();
        }

        if (joy_state & BUTTON_LEFT && !(last_joy_state & BUTTON_LEFT)) {

            if (selected_minigame_index == 0) {
                selected_minigame_index = num_minigames - 1;
            } else {
                selected_minigame_index--;
            }

            Menu_DrawTitle();
        }

        if (joy_state & BUTTON_START) {
            Menu_PlayMinigame();
        }

        last_joy_state = joy_state;
        SYS_doVBlankProcess();
    }

    return 0;
}
