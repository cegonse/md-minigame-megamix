#include <genesis.h>
#include "minigame.h"
#include "menu.h"

static Minigame_t *minigames;
static u8 selected_minigame_index;
static u8 num_minigames;

static u16 vram_pos = 16;

static void drawImageXY ( u16 plan, u16 prio, Image *image, u16 palette, u16 x, u16 y )
{
    SYS_disableInts();
    VDP_drawImageEx ( plan, image, TILE_ATTR_FULL ( palette, prio, 0, 0, vram_pos ), x, y, 0, 0 );
    SYS_enableInts();
    PAL_setPalette(palette, image->palette->data, DMA);

    vram_pos += image->tileset->numTile;
}

static void Menu_Draw(void)
{
    vram_pos = 16;

    VDP_setHorizontalScroll(BG_A, 0);
    VDP_setVerticalScroll(BG_A, 0);

    drawImageXY(BG_A, 0, &title_screen, PAL0, 0, 0);
    drawImageXY(BG_B, 1, &select_game, PAL1, 9, 2);

    VDP_drawText("Left, right: select minigame", 2, 24);
    VDP_drawText("Start: play", 2, 25);
}

static void Menu_DrawTitle(void)
{
    VDP_clearText(2, 10, 32);
    VDP_drawText(minigames[selected_minigame_index].title, 2, 10);
}

static void resetState(void)
{
    SYS_setVIntCallback(0);
	waitMs(500);
    waitMs(100);
	VDP_init();
    SPR_init();
	waitMs(500);
}

static void Menu_PlayMinigame(void)
{
    resetState();
    minigames[selected_minigame_index].run();
    resetState();

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
