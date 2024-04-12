// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "../../inc/types/player.h"

#include <stdio.h>

void set_username(Player *pl, const char *username) {
  snprintf(pl->username, MAX_USERNAME_LENGTH + 1, "%s", username);
}
const char *get_username(const Player *pl) { return pl->username; }

void set_id(Player *pl) {
  const char *username = get_username(pl);

  int i = 0;
  int id = 0;
  while (i < MAX_USERNAME_LENGTH) {
    id = id * ID_OFFSET + username[i];
    // id = id * ID_OFFSET + get_username(pl)[i]
    i = i + 1;
  }
  pl->id = id;
}
const int get_id(Player *pl) { return pl->id; }

void set_position(Player *pl, int position) { pl->position = position; }
const int get_position(const Player *pl) { return pl->position; }

void set_score(Player *pl, int score) { pl->score = score; }
const int get_score(const Player *pl) { return pl->score; }

void set_turns_blocked(Player *pl, int turns_blocked) {
  pl->turns_blocked = turns_blocked;
}
const int get_turns_blocked(const Player *pl) { return pl->turns_blocked; }
