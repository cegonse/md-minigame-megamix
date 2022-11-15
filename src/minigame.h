#pragma once

#define AddMinigame(ID, TITLE, RUN) \
    { \
        .id = #ID, \
        .title = TITLE, \
        .run = RUN \
    }

typedef struct minigame {
    char *id;
    char *title;
    void (*run)(void);
} Minigame;

struct minigame *Minigame_GetById(char *id);
