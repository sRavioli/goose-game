// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file private/handle_game.h
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

#ifndef GAME_MODULE_PRIVATE_H
#define GAME_MODULE_PRIVATE_H

#include "../handle_game.h"

void conform_username(char *username);
int is_username_valid(const char username[]);
char *ask_username(Players *pls, const int current_player);

void selection_sort_players(Players *players, int *dice_values);

void interactive_roll(Players *pls, int *dice_values);
void interactive_reroll(Players *pls, int *dice_values);
void print_players_list(Players *pls);

int check_square(const Board *board, int position);
void insert_goose_squares(Board *board);
void insert_special_squares(Board *board);

char *sq_to_str(const int square);

char *build_border(const char *borders[4], const int square_len, const int cols,
                   const int rows, const int row, const Board board);

char *build_squares(const char *vert, const int square_len, const int cols,
                    const int rows, const int row, const Board board);

#endif  // !GAME_MODULE_PRIVATE_H
