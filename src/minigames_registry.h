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


#define MINIGAMES                                        \
_MINIGAME(Pong,        "Pong")                  \
_MINIGAME(Tetris,      "Tetris")        \
_MINIGAME(Pang,        "Pang")           \
_MINIGAME(Slipstream,  "Slipstream")
