#pragma once

/* Add your minigame to the registry
 *
 * params:
 *
 * Base name of the handler function:
 *  void Pong_Main(void) -> Pong
 * 
 * Title:
 *  The title that would be displayed in the menu screen
 */


#define MINIGAMES                                   \
_MINIGAME(Pong,   "The best game")                  \
_MINIGAME(Tetris, "Russia's favourite game")        \
_MINIGAME(Pang,   "Bubble breaking time") 
