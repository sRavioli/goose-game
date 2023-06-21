// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

// #include "../inc/handle_leaderboard.h"
// #include "../inc/private/handle_leaderboard.h"

#include "../common/inc/logger.h"
#include "../common/inc/string.h"
#include "../common/inc/term.h"

#include "../common/inc/types/entries.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

// ---------------------

void append_entries(Entries *existing_entries, Entries *new_entries) {
  // Copy the new entries to the end of the existing array
  memcpy(get_entries(existing_entries) + get_num_entries(existing_entries),
         get_entries(new_entries),
         get_num_entries(new_entries) * sizeof(Entry));

  // Update the number of entries
  set_num_entries(existing_entries, get_num_entries(existing_entries) +
                                        get_num_entries(new_entries));
}

void swap_entries(Entry *first, Entry *second) {
  Entry temp = *first;
  *first = *second;
  *second = temp;
  return;
}

void rm_duplicate_entries(Entries *es) {
  int num_entries = get_num_entries(es);
  int i = 0;
  while (i < num_entries - 1) {
    Entry current = get_entry(es, i);
    Entry next = get_entry(es, i + 1);
    if (strcmp(get_name(&current), get_name(&next)) == 0) {
      int j = i + 1;
      while (j < num_entries - 1) {
        Entry e = get_entry(es, j + 1);
        set_entry(es, &e, j);
        j = j + 1;
      }
      num_entries = num_entries - 1;
      // Continue checking from this index to ensure no other duplicates were
      // missed
      i = i - 1;
    }
    i = i + 1;
  }
  return;
}

void sort_entries(Entries *es) {
  int num_entries = get_num_entries(es);
  int i = 0;
  while (i < num_entries) {
    int j = i + 1;
    while (j < num_entries) {
      Entry ei = get_entry(es, i);
      Entry ej = get_entry(es, j);
      int is_score_greater = get_final_score(&ej) > get_final_score(&ei);
      int is_score_equal = get_final_score(&ej) == get_final_score(&ei);
      int is_name_previous = strcmp(get_name(&ej), get_name(&ei)) < 0;
      int should_swap_entries =
          is_score_greater || (is_score_equal && is_name_previous);

      if (should_swap_entries) {
        swap_entries(&ei, &ej);
      }
      j = j + 1;
    }
    i = i + 1;
  }
  rm_duplicate_entries(es);

  return;
}

// ----------------------------------------------------------------------------

// int main(void) {
//   logger.start("test.log");
//   logger.log(__func__, "starting program");
//
//   logger.log(__func__, "stopping program");
//   logger.stop();
//   return 0;
// }
