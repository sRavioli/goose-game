// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file players.h
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
 * @date 2023-05-06 13:26
 * @version 1.0
 * @copyright GNU GPLv3
 */

#ifndef PLAYERS_TYPE_H
#define PLAYERS_TYPE_H

#include "./player.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @def MIN_NUM_PLAYERS
 * @brief The minimum number of players allowed in the game.
 */
#define MIN_NUM_PLAYERS 2

/**
 * @def MAX_NUM_PLAYERS
 * @brief The maximum number of players allowed in the game.
 */
#define MAX_NUM_PLAYERS 4

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Defines a struct for managing a list of players in the game.
 *
 * This struct contains an array of @c Player structs representing the players
 * in the game, as well as additional information such as the number of players
 * and the turn order.
 *
 * @var Players::players
 * An array of @c Player structs representing the players in the game.
 *
 * @var Players::players_num
 * The number of players in the game.
 *
 * @var Players::turn
 * The index of the current player in the turn order.
 */
typedef struct Players {
  Player players[MAX_NUM_PLAYERS];  ///< An array of @c Player structs
                                    ///< representing the players in the game.
  int players_num;                  ///< The number of players in the game.
} Players;

/**
 * @brief Returns the player at the specified position in the players array.
 *
 * This function returns a copy of the player struct stored at the specified
 * position in the players array of the Players struct.
 *
 * @param[in] pls      A pointer to the Players struct containing the players
 *                     array.
 * @param[in] position The index of the player to be returned.
 *
 * @return A pointer to the player struct stored at the specified position in
 *         the players array.
 */
Player *get_player(Players *pls, const int position);

/**
 * @brief Sets the player at the specified position in the players array.
 *
 * This function sets the player struct stored at the specified position in
 * the players array of the Players struct to the provided player struct.
 *
 * @param[in,out] pls      A pointer to the Players struct containing the
 *                         players array.
 * @param[in]     pl       A pointer to the player struct to be set.
 * @param[in]     position The index of the player to be set.
 *
 * @return void.
 */
void set_player(Players *pls, const Player *pl, const int position);

/**
 * @brief Returns the number of players in the players array of the Players
 * struct.
 *
 * This function returns the value of the players_num field of the Players
 * struct, which contains the number of players in the players array.
 *
 * @param[in] pls A pointer to the Players struct.
 *
 * @return The number of players in the players array of the Players struct.
 */
int get_players_num(const Players *pls);

/**
 * @brief Sets the number of players in the players array of the Players struct.
 *
 * This function sets the value of the players_num field of the Players struct
 * to the provided value, which represents the number of players in the
 * players array.
 *
 * @param[in,out] pls         A pointer to the Players struct.
 * @param[in]     players_num The new number of players in the players array.
 *
 * @return void.
 */
void set_players_num(Players *pls, const int players_num);

/**
 * @brief Swaps the positions of two players in the players list.
 *
 * This function swaps the positions of two players in the specified players
 * list. It retrieves the players at the given indices and swaps their positions
 * in the list. The players are swapped by copying their data into temporary
 * player variables, and then setting the players at the respective indices with
 * the swapped data.
 *
 * @param[in,out] pls        A pointer to the players list.
 * @param[in]     idx        The index of the first player to swap.
 * @param[in]     other_idx  The index of the second player to swap.
 *
 * @return void.
 */
void swap_players(Players *pls, const int idx, const int other_idx);

#endif  // !PLAYERS_TYPE_H
