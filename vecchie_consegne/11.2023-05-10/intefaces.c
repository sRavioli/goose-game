#include "./core/board.h"
#include "./core/entries.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 80
#define TITLE "IL GIOCO DELL'OCA\n"

void print_file(const char filename[]);
void print_title();
void print_center(char text[]);
void print_leaderboard(const char filename[]);

int main(void) {
  print_title();

  print_file("main_menu.txt");
  system("pause");

  print_file("help_menu.txt");
  system("pause");

  print_file("rules.txt");
  system("pause");

  print_file("manual.txt");
  system("pause");

  print_leaderboard("leaderboard.bin");
  system("pause");

  return EXIT_SUCCESS;
}

void print_file(const char filename[]) {
  FILE *fp;
  if (fopen_s(&fp, filename, "r") != 0) {
    printf("error: failed to open file '%s'\n", filename);
    exit(EXIT_FAILURE);
  }

  char line[MAX_LINE_LEN];
  while (fgets(line, MAX_LINE_LEN, fp)) {
    printf("%s", line);
  }
  fclose(fp);

  printf("\n");
}

void print_title() {
  print_center(TITLE);
  int i = 0;
  while (i < 80) {
    printf("-");
    i = i + 1;
  }
  printf("\n");
}

void print_center(char text[]) {
  int text_length = strlen(text);
  int remaining_space = 80 - text_length;
  // Center justification
  int left_space = remaining_space / 2;
  int right_space = remaining_space - left_space;
  int i = 0;
  while (i < left_space) {
    printf("%c", ' ');
    i = i + 1;
  }
  printf("%s", text);
}

void print_leaderboard(const char filename[]) {
  FILE *fp;
  if (fopen_s(&fp, filename, "rb") != 0) {
    printf("error: failed to open file '%s'\n", filename);
    exit(EXIT_FAILURE);
  }

  Entries entries[MAX_ENTRIES];
  fread(entries, sizeof(Entries), 1, fp);
  fclose(fp);

  printf("%6s  %6s  %5s\n", "RANK", "USERNAME", "SCORE");
  int i = 0;
  int rank = 1;
  int prev_score = -1;
  while (i < get_num_entries(entries)) {
    const Entry entry = *get_entry(entries, i);
    if (get_final_score(&entry) != prev_score) {
      prev_score = get_final_score(&entry);
      rank = i + 1;
    }
    printf("%6d  %6s  %6d\n", rank, get_name(&entry), get_final_score(&entry));
    i = i + 1;
  }
}
