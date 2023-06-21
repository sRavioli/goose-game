// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "../../inc/types/gamestate.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

void set_players(GameState *gs, Players pls) { gs->pls = &pls; }
Players *get_players(const GameState *gs) { return gs->pls; }

void set_board(GameState *gs, Board board) { gs->board = &board; }
Board *get_board(const GameState *gs) { return gs->board; }
