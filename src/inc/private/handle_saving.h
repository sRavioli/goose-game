// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file private/handle_saving.h
 * @brief This file contains private functions and declarations related to the
 *        saving module.
 *
 * The file includes necessary header files for game states from the common
 * module and the standard input/output library. It defines various helper
 * functions used internally by the saving module to facilitate saving and
 * loading game states.
 *
 * The functions in this file are responsible for tasks such as checking if a
 * file is empty, prompting the user to choose a save, reading saved game states
 * from a file, and writing the current game state to the save file.
 *
 * @note The functions in this file are intended for internal use within the
 *       saving module and should not be accessed or called directly from
 *       outside the module.
 *
 * @warning Modifying or calling these functions without proper understanding of
 *          their implementation may result in unexpected behavior and errors in
 *          the saving module.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-07-11 19:45
 * @version 1.1
 * @copyright GNU GPLv3
 */
#ifndef SAVING_MODULE_PRIVATE_H
#define SAVING_MODULE_PRIVATE_H

#include "../../common/inc/types/gamestates.h"

#include <stdio.h>

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Indicates that no saved games are present in a GameStates struct.
 */
#define NO_SAVED_GAMES 0

/**
 * @brief Indicates to quit the game.
 */
#define QUIT_GAME -1

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Asks the user to choose a save and returns the selected index.
 *
 * This function displays the available save games and prompts the user to
 * choose one. It prints the game name, number of players, player names with
 * their positions, and the board size for each save game. The user is then
 * prompted to enter the index of the desired save game. The function validates
 * the input and repeats the prompt until a valid index is entered. The chosen
 * index is returned.
 *
 * @param[in] gss The GameStates struct containing the available save games.
 *
 * @return The index of the chosen save game.
 */
int choose_save(GameStates gss);

/**
 * @brief Reads the saved game states from a file.
 *
 * This function attempts to read the saved game states from the specified file.
 * If the file is not readable or empty, it sets the number of games to
 * `NO_SAVED_GAMES`. Otherwise, it reads the game states from the file into the
 * provided GameStates struct.
 *
 * @param[in,out] gss The GameStates struct to store the read game states.
 *
 * @return void.
 */
void read_saves(GameStates *gss);

/**
 * @brief Writes the current game state to the save file.
 *
 * This function attempts to save the current game state to the save file.
 * It first reads the existing game states from the file into a GameStates
 * struct. If the number of saves is within bounds, the current game state is
 * appended to the struct. If the maximum number of saves is reached, the user
 * is prompted to choose a game to overwrite. The updated GameStates struct is
 * then written back to the file.
 *
 * @param[in] gs The GameState struct representing the current game state to
 *               save.
 *
 * @return void.
 */
void write_save(GameState gs);

#endif  // !SAVING_MODULE_PRIVATE_H
