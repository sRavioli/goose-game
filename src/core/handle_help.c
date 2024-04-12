// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include <conio.h>
#include <stdio.h>

#include "../common/inc/string.h"
#include "../common/inc/term.h"
#include "../inc/globals.h"

#include "../inc/handle_help.h"

void help_menu() {
  print_menu(HELP_MENU);

  int menu_loop = TRUE;
  while (menu_loop) {
    char key = _getch();

    if (key == 'r') {
      display_file(RULES_FILE);
      print_menu(HELP_MENU);
    } else if (key == 'm') {
      display_file(MANUAL_FILE);
      print_menu(HELP_MENU);
    } else if (key == 'b') {
      menu_loop = FALSE;
    }
  }
}
