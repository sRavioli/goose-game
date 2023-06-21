// Copyright (c) 2023 @authors. GNU GPLv3
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./common/inc/logger.h"
#include "./common/inc/term.h"

#include "./inc/errors.h"
#include "./inc/globals.h"

#include "./inc/handle_game.h"
#include "./inc/handle_help.h"

void main_menu() {
  logger.enter_fn(__func__);

  new_screen();
  print_menu(MAIN_MENU);

  logger.exit_fn();
}

int main(void) {
  logger.start("goose.log");
  logger.enter_fn(__func__);

  srand(time(NULL));
  main_menu();

  int menu_loop = TRUE;
  while (menu_loop) {
    char key = _getch();

    if (key == 'n') {
      logger.log("launching new game");
      new_game();
      main_menu();
    } else if (key == 's') {
      clear_line();
      printf("DEBUG: key %c: [s]ave games", key);
      logger.log("invoked saved games");
    } else if (key == 'l') {
      // leaderboard();
      clear_line();
      printf("DEBUG: key %c: [l]eaderboard", key);
      logger.log("invoked leaderboard");
    } else if (key == 'h') {
      logger.log(__func__, "calling help menu");
      help_menu();
      main_menu();
    } else if (key == 'q' || key == ESC) {
      clear_line();
      printf("DEBUG: (%c) exiting...", key);
      _fcloseall();
      logger.log("exiting game");
      menu_loop = FALSE;
    } else {
      clear_line();
      print_err(INVALID_KEY_ERROR, key);
      logger.log("invalid key pressed, continuing loop");
    }
  }

  // logger.exit_fn();
  logger.stop();
  return 0;
}
