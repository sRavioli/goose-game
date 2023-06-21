// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file handle_game.h
 * @brief ...
 *
 * ...
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date ...
 * @version 1.0
 * @copyright GNU GPLv3
 */
#ifndef GAME_MODULE_H
#define GAME_MODULE_H

#include "../common/inc/types/board.h"
#include "../common/inc/types/players.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

int ask_num_in_range(const int min, const int max, const char name[]);
Players *create_players(const int num_players);

void sort_players_by_dice(Players *pls);

Board *create_board(const int dim);

/**
 * @brief Build the game board as a string.
 *
 * This function takes a @c Board structure, along with other parameters, and
 * creates a string representation of the game board. The resulting string
 * includes the border characters specified in the @c borders array.
 *
 * @param[in] board      The @c Board structure to represent as a string
 * @param[in] cols       The number of columns in the game board
 * @param[in] square_len The length of one side of a square on the game board
 * @param[in] borders    An array of eight characters to use as the border
 *                       characters for the game board. The characters will be
 *                       used in the following order:
 *                       - nw_corner (ex. "┌")
 *                       - ne_corner (ex. "┐")
 *                       - sw_corner (ex. "└")
 *                       - se_corner (ex. "┘")
 *                       - join_down (ex. "┬")
 *                       - join_up (ex. "┴")
 *                       - dash (ex. "─")
 *                       - vert (ex. "│")
 * @return A string representation of the game board
 */
char *build_board(const Board board, const int cols, const int square_len,
                  const char *borders[8]);

/**
 * @brief Prints the game board to stdout.
 *
 * This function prints the provided game board to stdout using the @c printf()
 * function.
 *
 * @param board The game board to print.
 *
 * @return void.
 */
void print_board(const char game_board[]);

void print_positions(Players *pls);

void new_game();
void dev_game_loop(Players *pls, Board *board, const char game_board[]);
void leave_game(void *ptr, ...);

#endif  // !GAME_MODULE_H
