// Copyright (c) 2023 @authors. GNU GPLv3
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "../../inc/types/gamestates.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

GameState *get_gamestate(GameStates *gss, const int position) {
  return &gss->gamestates[position];
}
void set_gamestate(GameStates *gss, GameState gs, const int position) {
  gss->gamestates[position] = gs;
}

int get_num_games(const GameStates *gss) { return gss->num_games; }
void set_num_games(GameStates *gss, const int num_games) {
  gss->num_games = num_games;
}
