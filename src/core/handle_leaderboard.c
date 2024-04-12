// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "../inc/globals.h"
#include "../inc/inputs.h"

#include "../common/inc/error.h"
#include "../common/inc/logger.h"
#include "../common/inc/string.h"
#include "../common/inc/term.h"

#include "../common/inc/types/entries.h"

#include "../inc/handle_leaderboard.h"
#include "../inc/private/handle_leaderboard.h"

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

void read_leaderboard(Entries *es) {
  logger.enter_fn(__func__);
  logger.log("attempting to read leaderboard");

  FILE *fp;
  if (fopen_s(&fp, LEADERBOARD_FILE, "rb")) {
    throw_err(FILE_NOT_READABLE_ERROR);
  }

  if (is_file_empty(fp)) {
    logger.log("the leaderboard is empty");
    set_num_entries(es, NO_ENTRIES);
  } else {
    logger.log("reading leaderboard from file");
    fread(es, sizeof(*es), 1, fp);
  }
  fclose(fp);

  logger.exit_fn();
}

int find_duplicate_entry(Entries es, Entry e) {
  logger.enter_fn(__func__);
  logger.log("searching for another entry with username '%s'", get_name(&e));

  int index = INDEX_NOT_FOUND;

  int i = 0;
  while (i < get_num_entries(&es)) {
    const Entry ei = get_entry(&es, i);
    if (strcmp(get_name(&e), get_name(&ei)) == 0) {
      index = i;
    }
    i = i + 1;
  }

  logger.exit_fn();
  return index;
}

void swap_entries(Entry *first, Entry *second) {
  logger.enter_fn(__func__);
  logger.log("swapping %s with %s", get_name(first), get_name(second));

  Entry temp = *first;
  *first = *second;
  *second = temp;

  logger.exit_fn();
  return;
}

void rm_duplicate_entries(Entries *es) {
  logger.enter_fn(__func__);
  logger.log("removing duplicate entries");

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

  logger.exit_fn();
  return;
}

void sort_entries(Entries *es) {
  logger.enter_fn(__func__);
  logger.log("sorting entries");

  int num_entries = get_num_entries(es) - 1;
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

  logger.exit_fn();
  return;
}

void write_leaderboard(Entry e) {
  logger.enter_fn(__func__);
  logger.log("attempting to save current entry");

  Entries leaderboard;
  read_leaderboard(&leaderboard);
  int num_entries = get_num_entries(&leaderboard);
  logger.log("read %i entries in leaderboard", num_entries);

  int write_idx = num_entries;
  int count = num_entries;
  if (num_entries != NO_ENTRIES) {
    write_idx = write_idx - 1;
  }

  logger.log("searching for a duplicate entry");
  int duplicate_idx = find_duplicate_entry(leaderboard, e);
  if (duplicate_idx != INDEX_NOT_FOUND) {
    logger.log("duplicate found at pos. %i", duplicate_idx);
    Entry duplicate = get_entry(&leaderboard, duplicate_idx);
    // score in leaderboard is greater, do not write
    if (get_final_score(&duplicate) > get_final_score(&e)) {
      logger.log("score in file is greater than given score, not writing");
      logger.exit_fn();
      return;
    }
    logger.log("score in file is lesser, writing");

    write_idx = duplicate_idx;
    logger.log("set writing index as %i", duplicate_idx);
  }
  logger.log("no duplicate found");

  if (num_entries == MAX_ENTRIES) {
    logger.log("reached max number of entries in leaderboard");

    logger.log("checking if the last entry has lower score than given one");
    Entry last = get_entry(&leaderboard, MAX_ENTRIES - 1);
    if (get_final_score(&last) > get_final_score(&e)) {
      logger.log("last entry has greater score, not writing");
      logger.exit_fn();
      return;
    }
    logger.log("entry has greater score, overwriting");
  } else {
    logger.log("appending");
    count = count + 1;
  }

  logger.log("setting entry in leaderboard");
  set_entry(&leaderboard, &e, write_idx);
  set_num_entries(&leaderboard, count);
  sort_entries(&leaderboard);

  FILE *fp;
  if (fopen_s(&fp, LEADERBOARD_FILE, "wb")) {
    throw_err(FILE_NOT_WRITABLE_ERROR);
  }
  fwrite(&leaderboard, sizeof(leaderboard), 1, fp);
  fclose(fp);

  logger.log("wrote leaderboard to file");
  logger.exit_fn();
}

void print_leaderboard(Entries es) {
  logger.enter_fn(__func__);
  logger.log("printing leaderboard");
  new_screen();
  printf("\n\n");

  if (get_num_entries(&es) == NO_ENTRIES) {
    logger.log("leaderboard is empty");
    print_err(EMPTY_LEADERBOARD);
    logger.exit_fn();
    return;
  }

  int width, heigth;
  get_term_size(&width, &heigth);
  int padding = (width - strlen(LEADERBOARD_BANNER) - 1) / 2;

  logger.log("leaderboard is NOT empty.");
  printf("%*c%s", padding, SPACE_CHAR, LEADERBOARD_BANNER);
  int i = 0;
  int rank = 1;
  int prev_score = -1;

  while (i < get_num_entries(&es)) {
    Entry e = get_entry(&es, i);
    if (get_final_score(&e) != prev_score) {
      prev_score = get_final_score(&e);
      rank = i + 1;
    }
    printf("%*c%3d  %5s  %5d\n", padding, SPACE_CHAR, rank, get_name(&e),
           get_final_score(&e));
    i = i + 1;
  }

  logger.log("printed %i entries", i);
  logger.exit_fn();
}

void display_leaderboard(Entries es) {
  logger.enter_fn(__func__);
  logger.log("displayin leaderboard");

  print_leaderboard(es);
  printf("\n\n");
  printf("Exit this view by pressing b/ESC/ENTER/SPACEBAR");

  logger.log("waiting for back key...");
  int display = TRUE;
  while (display) {
    char key = _getch();
    if (is_back_key(key)) {
      display = FALSE;
    }
  }

  logger.log("exiting this view");
  logger.exit_fn();
}

void leaderboard(void) {
  logger.enter_fn(__func__);
  logger.log("attempting to display leaderboard");

  Entries leaderboard;
  read_leaderboard(&leaderboard);

  display_leaderboard(leaderboard);

  logger.log("exited leaderboard view");
  logger.exit_fn();
}
