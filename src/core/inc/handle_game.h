// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef GAME_MODULE_H
#define GAME_MODULE_H

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Start a new game.
 *
 * This function initializes a new game by creating a new screen, asking the
 * user for the number of squares and players, creating the game board, sorting
 * the players by dice, and starting the game loop. It utilizes several helper
 * functions to perform these tasks. The appearance of the screen and the user
 * input handling depends on the underlying platform.
 *
 * @note The function uses platform-specific methods to create a new screen, ask
 *       the user for input, create the game board, sort players, and start the
 *       game loop.
 */
void new_game();

#endif  // !GAME_MODULE_H
