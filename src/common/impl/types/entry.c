// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "../../inc/types/entry.h"

#include <stdio.h>

const char *get_name(const Entry *e) { return e->name; }
void set_name(Entry *e, const char name[]) {
  snprintf(e->name, MAX_USERNAME_LENGTH + 1, "%s", name);
}

const int get_final_score(const Entry *e) { return e->final_score; }
void set_final_score(Entry *e, int final_score) {
  e->final_score = final_score;
}
