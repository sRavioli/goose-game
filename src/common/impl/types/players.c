// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "../../inc/types/players.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

Player *get_player(Players *pls, const int position) {
  return &pls->players[position];
}
void set_player(Players *pls, const Player *pl, const int position) {
  pls->players[position] = *pl;
}

int get_players_num(const Players *pls) { return pls->players_num; }
void set_players_num(Players *pls, const int players_num) {
  pls->players_num = players_num;
}

// int get_turn(const Players *pls) { return pls->turn; }
// void set_turn(Players *pls, const int turn) { pls->turn = turn; }

void swap_players(Players *pls, const int idx, const int other_idx) {
  Player player1 = *get_player(pls, idx);
  Player player2 = *get_player(pls, other_idx);

  set_player(pls, &player2, idx);
  set_player(pls, &player1, other_idx);
}
