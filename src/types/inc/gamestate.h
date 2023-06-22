// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef GAMESTATE_TYPE_H
#define GAMESTATE_TYPE_H

#include "./board.h"
#include "./players.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

typedef struct GameState {
  Players *pls;
  Board *board;
  char game_board[];
} GameState;

// typedef struct GameStates {
//   GameState games[5];
//   int num_games;
// } GameStates;

/**
 * @brief Sets the players of the game state.
 *
 * This function sets the players of the game state to the specified players.
 *
 * @param[in,out] gs   A pointer to the game state.
 * @param[in]     pls  The players to set.
 *
 * @return void.
 */
void set_players(GameState *gs, const Players pls);

/**
 * @brief Gets the players of the game state.
 *
 * This function returns the players of the game state.
 *
 * @param[in] gs  A pointer to the game state.
 *
 * @return The players of the game state.
 */
Players *get_players(const GameState *gs);

/**
 * @brief Sets the board of the game state.
 *
 * This function sets the board of the game state to the specified board.
 *
 * @param[in,out] gs     A pointer to the game state.
 * @param[in]     board  The board to set.
 *
 * @return void.
 */
void set_board(GameState *gs, const Board board);

/**
 * @brief Gets the board of the game state.
 *
 * This function returns the board of the game state.
 *
 * @param[in] gs  A pointer to the game state.
 *
 * @return The board of the game state.
 */
Board *get_board(const GameState *gs);

#endif  // !GAMESTATE_TYPE_H
