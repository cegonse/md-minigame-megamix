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

Minigame_t const * Minigame_GetById(const minigameId id) {
    return &minigame_registry[id];
}
