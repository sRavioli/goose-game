// Copyright (c) 2023 Simone Fidanza – GNU GPLv3
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define MAX_USERNAME_LENGTH 3

typedef struct {
  char name[MAX_USERNAME_LENGTH + 1];
  int score;
} Entry;

int read_entries(Entry entries[], const char *filename);
void write_entries(Entry entries[], int num_entries, const char *filename);
void print_leaderboard(Entry entries[], int num_entries);

#endif // !LEADERBOARD_H
