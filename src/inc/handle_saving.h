// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file handle_saving.h
 * @brief This file contains functions related to the saving module.
 *
 * The file includes necessary header files for board and player types from the
 * common module. It defines functions for saving the current game state to a
 * file and displaying the available saved games.
 *
 * The `save_game()` function prompts the user to enter a name for the save and
 * creates a `GameState` struct containing the current players and board. It
 * then passes the game state to the `write_save()` function to save it to the
 * file.
 *
 * The `saved_games()` function reads the saved game states from the file and
 * checks the number of available saves. If no saves are found, it displays a
 * corresponding message. If only one save is found, it prompts the user to
 * launch that game. If multiple saves are found, it prompts the user to choose
 * a save and launches the selected game.
 *
 * @note The functions in this file depend on the types defined in the "board.h"
 *       and "players.h" header files from the common/inc/types module. Make
 *       sure to include those headers before using the functions.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-07-08 13:00
 * @version 1.0
 * @copyright GNU GPLv3
 */
#ifndef SAVING_MODULE_H
#define SAVING_MODULE_H

#include "../common/inc/types/board.h"
#include "../common/inc/types/players.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Saves the current game state to a file.
 *
 * This function prompts the user to enter a name for the save and creates a
 * `GameState` struct containing the current players and board. The game state
 * is then passed to the `write_save()` function to save it to the file.
 *
 * @param[in] pls   The Players struct representing the current players in the
 *                  game.
 * @param[in] board The Board struct representing the current game board.
 *
 * @return void.
 */
void save_game(Players *pls, Board *board);

/**
 * @brief Displays the available saved games and prompts the user to choose one.
 *
 * This function reads the saved game states from the file and checks the number
 * of available saves. If no saves are found, it displays a corresponding
 * message. If only one save is found, it prompts the user to launch that game.
 * If multiple saves are found, it prompts the user to choose a save and
 * launches the selected game.
 *
 * @return void.
 */
void saved_games();

#endif  // !SAVING_MODULE_H
