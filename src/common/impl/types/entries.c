// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "../../inc/types/entries.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

const int get_num_entries(const Entries *es) { return es->num_entries; }
void set_num_entries(Entries *es, const int num_entries) {
  es->num_entries = num_entries;
}

Entry *get_entries(Entries *es) { return es->entries; }

Entry get_entry(Entries *es, const int position) {
  return es->entries[position];
}
void set_entry(Entries *es, Entry *e, const int position) {
  es->entries[position] = *e;
}
