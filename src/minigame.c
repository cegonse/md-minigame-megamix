#include "minigame.h"
#include "genesis.h"

extern int num_minigames;
extern struct minigame minigame_registry[];

struct minigame *Minigame_GetById(char *id) {
    u8 i;

    for (i=0; i<num_minigames; ++i) {
        if (strcmp(id, minigame_registry[i].id) == 0) {
            return &minigame_registry[i];
        }
    }

    return NULL;
}
