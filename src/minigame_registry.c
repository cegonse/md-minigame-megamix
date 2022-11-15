#include "minigame.h"

extern void Pong_Main(void);
extern void Tetris_Main(void);
extern void Pang_Main(void);

const Minigame const minigame_registry[] = {
    AddMinigame(pong, "Pong, the best game", Pong_Main),
    AddMinigame(tetris, "Russia's favourite game", Tetris_Main),
    AddMinigame(pang, "Bubble breaking time", Pang_Main)
};

const int num_minigames = sizeof(minigame_registry) / sizeof(Minigame);
