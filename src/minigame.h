#pragma once

#include <genesis.h>
#include "minigames_registry.h"

typedef struct minigame
{
    char *title;
    void (*run)(void);
} Minigame_t;

#define _MINIGAME(game, title) game,
typedef enum id
{
    MINIGAMES
} minigameId;
#undef _MINIGAME

Minigame_t const *Minigame_GetById(const minigameId id);

Minigame_t const *Minigame_GetAll(void);

u8 Minigame_Count(void);
