#include <genesis.h>
#include "minigame.h"

#define _MINIGAME(game, msg) extern void game##_Main(void);
MINIGAMES
#undef _MINIGAME

#define _MINIGAME(game, msg)    \
{                               \
    .title = #msg,              \
    .run = game##_Main          \
},                              \

const Minigame_t const minigame_registry[] = {
    MINIGAMES
};

Minigame_t const *Minigame_GetById(const minigameId id) {
    return &minigame_registry[id];
}

Minigame_t const *Minigame_GetAll(void) {
    return minigame_registry;
}

u8 Minigame_Count(void) {
    return sizeof(minigame_registry) / sizeof(Minigame_t);
}
