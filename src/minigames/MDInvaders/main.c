#include <genesis.h>
#include "MDInvaders.h"

#define INVADER_NUMBER  (5 * 11)
#define INVADER_SPEED   1

struct Invader
{
    Sprite* sprite;
    s16 dirX;
    s16 dirY;
};

struct Invader invaders[INVADER_NUMBER];

void createInvaders()
{
    PAL_setPalette(PAL2, invader01.palette->data, DMA);

    for(s16 i = 0; i < INVADER_NUMBER; ++ i)
    {
        struct Invader* invader = &invaders[i];

        const s16 x = random() % screenWidth;
        const s16 y = random() % (screenHeight - 50);

        invader->sprite = SPR_addSprite(&invader01, x, y, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
        SPR_setFrame(invader->sprite, random() % 4);

        invader->dirX = random() % 2 == 0? -INVADER_SPEED : INVADER_SPEED;
        invader->dirY = random() % 2 == 0? -INVADER_SPEED : INVADER_SPEED;
    }
}

void updateInvaders(s8 updateAnimation)
{
    for(s16 i = 0; i < INVADER_NUMBER; ++ i)
    {
        struct Invader* invader = &invaders[i];

        s16 newX = invader->sprite->x - 0x80 + invader->dirX;

        if(newX <= 0)
        {
            invader->dirX = INVADER_SPEED;
            newX = 0;
        }
        else if(newX >= screenWidth - invader->sprite->definition->w)
        {
            invader->dirX = -INVADER_SPEED;
            newX = screenWidth - invader->sprite->definition->w;
        }

        s16 newY = invader->sprite->y - 0x80 + invader->dirY;

        if(newY <= 0)
        {
            invader->dirY = INVADER_SPEED;
            newY = 0;
        }
        else if(newY >= screenHeight - invader->sprite->definition->h)
        {
            invader->dirY = -INVADER_SPEED;
            newY = screenHeight - invader->sprite->definition->h;
        }

        SPR_setPosition(invader->sprite, newX, newY);
    }

    if(updateAnimation)
    {
        for(s16 i = 0; i < INVADER_NUMBER; ++ i)
        {
            SPR_nextFrame(invaders[i].sprite);
        }
    }
}

void MDInvaders_Main()
{
    u16 joy_state;

    //PAL_setColors(0, (u16*)palette_black, 64, CPU);

    createInvaders();

    PAL_setPalette(PAL0, background.palette->data, DMA);
    VDP_drawImageEx(BG_A, &background, TILE_ATTR_FULL(PAL0, 0, 0, 0, 5), 0, 0, 0, TRUE);

    fix16 timeCounter = 0;

    while(1)
    {
        //VDP_drawImageEx(BG_A, &background, TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 0, 0, 1, 0);

        joy_state = JOY_readJoypad(JOY_1);

        if (joy_state & BUTTON_START)
        {
            break;
        }

        ++ timeCounter;

        updateInvaders(timeCounter >= 8);

        if(timeCounter >= 8)
        {
            timeCounter = 0;
        }

        //VDP_showFPS(SYS_getFPSAsFloat());

        SPR_update();

        VDP_showCPULoad();
        SYS_doVBlankProcess();
    }
}
