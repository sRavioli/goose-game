// Copyright (c) 2023 @authors. GNU GPLv3
#ifndef GAMESTATES_TYPE_H
#define GAMESTATES_TYPE_H

#define MAX_SAVED_GAMES 5

#include "./gamestate.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

typedef struct GameStates {
  GameState gamestates[MAX_SAVED_GAMES];
  int num_games;
} GameStates;

GameState *get_gamestate(GameStates *gss, const int position);
void set_gamestate(GameStates *gss, GameState gs, const int position);

int get_num_games(const GameStates *gss);
void set_num_games(GameStates *gss, const int num_games);

#endif  // !GAMESTATES_TYPE_H
