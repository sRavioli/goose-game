// Copyright (c) 2023 Simone Fidanza – GNU GPLv3
#include "./leaderboard.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_ENTRIES 10

void clear_screen() {
  // first clear the console, then move the cursor to the top left corner
  // this solution makes the content accessible by scrolling
  printf("\033[2J");
  printf("\033[%d;%dH", 0, 0);

  // using a system call solves the issue
  // system("cls");
}
void clear_line() { printf("\r\x1b[K"); }

void logo() {
  clear_screen();
  printf(
      "  _____   _          _____   _____    ____     _____    ____        \n"
      " |_   _| | |        / ____| |_   _|  / __ \\   / ____|  / __ \\     \n"
      "   | |   | |       | |  __    | |   | |  | | | |      | |  | |      \n"
      "   | |   | |       | | |_ |   | |   | |  | | | |      | |  | |      \n"
      "  _| |_  | |____   | |__| |  _| |_  | |__| | | |____  | |__| |      \n"
      " |_____| |______|   \\_____| |_____|  \\____/   \\_____|  \\____/   \n"
      "                                                                    \n"
      "                                                                    \n"
      "  _____    ______   _        _      _  ____     _____               \n"
      " |  __ \\  |  ____| | |      | |    ( )/ __ \\   / ____|     /\\    \n"
      " | |  | | | |__    | |      | |    |/| |  | | | |         /  \\     \n"
      " | |  | | |  __|   | |      | |      | |  | | | |        / /\\ \\   \n"
      " | |__| | | |____  | |____  | |____  | |__| | | |____   / ____ \\   \n"
      " |_____/  |______| |______| |______|  \\____/   \\_____| /_/    "
      "\\_\\\n\n\n");

  char press[26] = "Press any key to continue";
  char dots[4][4] = {".  ", ".. ", "...", "   "};
  int display_logo = 1;
  while (display_logo) {
    // Print the spinner animation
    int i = 0;
    while (!_kbhit()) {
      if (i % 4 == 0) {
        printf("%s \b%s\r", press, dots[0]);
      } else if (i % 4 == 1) {
        printf("%s \b%s\r", press, dots[1]);
      } else if (i % 4 == 2) {
        printf("%s \b%s\r", press, dots[2]);
      } else if (i % 4 == 3) {
        printf("%s \b%s\r", press, dots[3]);
      }
      i = i + 1;
      Sleep(500);
    }
    // consume the key pressed before otherwise it will be passed to the main
    // _getch() and interfere with it.
    _getch();

    // exit
    display_logo = 0;
  }
}

void main_menu() {
  clear_screen();
  printf("MAIN MENU:\n"
         "[n]ew game\n"
         "[s]aved games\n"
         "[l]eaderboard\n"
         "[h]elp\n"
         "[q]uit\n");
}

void leaderboard() {
  Entry entries[MAX_ENTRIES];
  int num_entries = read_entries(entries, "leaderboard.txt");

  clear_screen();
  print_leaderboard(entries, num_entries);
  printf("\nExit with q/ESC/ENTER\n");
  int display_leaderboard = 1;
  while (display_leaderboard) {
    char leaderch = _getch();
    if (leaderch == 27 || leaderch == 'q' || leaderch == 13) {
      display_leaderboard = 0;
    }
  }
  main_menu();
}

int main() {
  logo();

  main_menu();

  int main_menu_loop = 1;
  while (main_menu_loop) {
    char key = _getch();

    if (key == 'n') {
      clear_line();
      printf("DEBUG: key %c: [n]ew game", key);
    } else if (key == 's') {
      clear_line();
      printf("DEBUG: key %c: [s]ave games", key);
    } else if (key == 'l') {
      leaderboard();
    } else if (key == 'h') {
      clear_line();
      printf("DEBUG: key %c: [h]elp", key);
    } else if (key == 'q' || key == 27) {
      clear_line();
      printf("DEBUG: (%c) exiting...", key);
      main_menu_loop = 0;
    } else {
      clear_line();
      printf("Pressed key %c, it does nothing.", key);
    }
  }

  return 0;
}
