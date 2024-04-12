// Copyright (c) 2023 @authors. GNU GPLv3
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "../common/inc/types/board.h"
#include "../common/inc/types/gamestate.h"
#include "../common/inc/types/gamestates.h"
#include "../common/inc/types/player.h"
#include "../common/inc/types/players.h"

#include "../common/inc/error.h"
#include "../common/inc/logger.h"
#include "../common/inc/string.h"
#include "../common/inc/term.h"

#include "../inc/globals.h"

#include "../inc/handle_game.h"
#include "../inc/handle_saving.h"
#include "../inc/private/handle_saving.h"

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *BORDERS[8] = DEFAULT_BORDERS;

// for debugging purposes
void print_gamestates(GameStates gss) {
  printf("GameStates gss: {\n");
  printf("  saved games: %i\n", gss.num_games);
  int i = 0;
  while (i < gss.num_games) {
    GameState gs = gss.gamestates[i];
    Board board = gss.gamestates[i].board;
    Players pls = gss.gamestates[i].pls;
    printf("  GameState[] gss.gamestates[%i]: {\n", i);
    printf("    game name: '%s'\n", gs.game_name);
    printf("    Board gss.gamestates[%i].board: {\n", i);
    printf("      dimension: %i\n", board.dim);
    printf("      squares[]: [");
    int j = 0;
    while (j < board.dim) {
      printf("%i", board.squares[j]);
      if (j < board.dim - 1) {
        printf(", ");
      }
      j = j + 1;
    }
    printf("]\n");
    printf("    }\n");
    printf("    Players[] gss.gamestates[%i].pls: {\n", i);
    printf("      players number: %i\n", pls.players_num);
    int k = 0;
    while (k < pls.players_num) {
      printf("      Player gss.gamestates[%i].pls.players[%i]: {\n", i, k);
      printf("        id: %i\n", pls.players[k].id);
      printf("        score: %i\n", pls.players[k].score);
      printf("        position: %i\n", pls.players[k].position);
      printf("        turns blocked: %i\n", pls.players[k].turns_blocked);
      printf("        username: %s\n", pls.players[k].username);
      k = k + 1;
    }
    printf("    }\n");
    printf("  }\n");
    i = i + 1;
  }
  printf("}\n");

  wait_keypress("press to continue");
}

int choose_save(GameStates gss) {
  logger.enter_fn(__func__);
  logger.log("attempting to ask user to choose a save");

  printf("Please select a save from the following ones:\n");
  int num_saves = get_num_games(&gss);
  int i = 0;
  while (i < num_saves) {
    GameState gs = *get_gamestate(&gss, i);
    Players pls = get_players(&gs);
    Board board = get_board(&gs);

    printf("%i) \"%s\":\n", i, get_game_name(&gs));
    printf("    * players (%i): [", get_players_num(&pls));
    int j = 0;
    while (j < get_players_num(&pls)) {
      Player pl = *get_player(&pls, j);
      printf("%s (pos. %i)", get_username(&pl), get_position(&pl) + 1);
      if (j < get_players_num(&pls) - 1) {
        printf(", ");
      }
      j = j + 1;
    }
    printf("]\n");
    printf("    * board with %i squares\n", get_dim(&board));
    i = i + 1;
  }
  printf("\nSelect a game or [q]uit and go back to the menu");
  printf("\n> ");

  int input;
  char buffer[4];
  int invalid_input = FALSE;

  do {
    fgets(buffer, sizeof(buffer), stdin);

    if (buffer[0] == 'q') {
      input = QUIT_GAME;
      break;
    }

    if (buffer[0] < '0' || buffer[0] > '4') {
      invalid_input = TRUE;
      print_err(INVALID_INPUT_ERROR);
      printf("\n> ");
      continue;
    }

    input = atoi(buffer);

    if (input < NO_SAVED_GAMES || input > get_num_games(&gss) - 1) {
      invalid_input = TRUE;
      print_err(INVALID_GAME);
      printf("\n> ");
    } else {
      invalid_input = FALSE;
    }
  } while (invalid_input);

  logger.exit_fn();
  return input;
}

void read_saves(GameStates *gss) {
  logger.enter_fn(__func__);
  logger.log("attempting to read saves");

  FILE *fp;
  if (fopen_s(&fp, SAVED_GAMES_FILE, "rb")) {
    logger.log("file is not readable");
    throw_err(FILE_NOT_READABLE_ERROR);
  }

  if (is_file_empty(fp)) {
    logger.log("no saves in file");
    set_num_games(gss, NO_SAVED_GAMES);
  } else {
    logger.log("reading saves from file");
    fread(gss, sizeof(*gss), 1, fp);
  }
  fclose(fp);

  // print_gamestates(*gss);

  logger.exit_fn();
}

void write_save(GameState gs) {
  logger.enter_fn(__func__);
  logger.log("attempting to save current game");

  GameStates file_gss;
  read_saves(&file_gss);

  int num_saves = get_num_games(&file_gss);
  logger.log("currently present %i saves", num_saves);

  if (num_saves >= NO_SAVED_GAMES && num_saves < MAX_SAVED_GAMES) {
    logger.log("num_saves is inside bounds, appending to struct");
    set_gamestate(&file_gss, gs, get_num_games(&file_gss));
    set_num_games(&file_gss, get_num_games(&file_gss) + 1);
  } else if (num_saves == MAX_SAVED_GAMES) {
    logger.log("max number of saves reached, asking game to overwrite");
    new_screen();
    print_err(LIMIT_SAVES);
    printf("\n");

    int index = choose_save(file_gss);
    set_gamestate(&file_gss, gs, index);  // overwrite at index
  }

  FILE *fp;
  if (fopen_s(&fp, SAVED_GAMES_FILE, "wb")) {
    logger.log("file is not writable");
    throw_err(FILE_NOT_WRITABLE_ERROR);
  }
  fwrite(&file_gss, sizeof(file_gss), 1, fp);
  fclose(fp);

  logger.log("writing saves to file");

  // print_gamestates(file_gss);  // debug
  logger.exit_fn();
}

void save_game(Players *pls, Board *board) {
  char game_name[MAX_BUFFER_LEN];
  printf("Insert the name of the save: ");
  fgets(game_name, MAX_BUFFER_LEN, stdin);
  game_name[strlen(game_name) - 1] = '\0';

  GameState gs;
  set_players(&gs, pls);
  set_board(&gs, board);
  set_game_name(&gs, game_name);

  write_save(gs);
}

void saved_games() {
  logger.enter_fn(__func__);
  logger.log("checking if saves are present");

  GameStates gss;
  read_saves(&gss);

  if (get_num_games(&gss) == 0) {
    print_err(NO_SAVES);
    printf("\n");

    printf("Exit this view by pressing b/ESC/ENTER/SPACEBAR");

    logger.log("waiting for back key...");
    int display = TRUE;
    while (display) {
      char key = _getch();
      if (is_back_key(key)) {
        display = FALSE;
      } else {
        printf("\n");
        print_err(INVALID_KEY_ERROR);
      }
    }

  } else if (get_num_games(&gss) == 1) {
    printf("Found only the following game: ");

    GameState gs = *get_gamestate(&gss, 0);
    Players pls = get_players(&gs);
    Board board = get_board(&gs);

    printf("\n%s : \n", get_game_name(&gs));
    printf("    * players: [", get_players_num(&pls));
    int j = 0;
    while (j < get_players_num(&pls)) {
      Player pl = *get_player(&pls, j);
      printf("%s (pos. %i)", get_username(&pl), get_position(&pl) + 1);
      if (j < get_players_num(&pls) - 1) {
        printf(", ");
      }
      j = j + 1;
    }
    printf("]\n");
    printf("    * board with %i squares\n", get_dim(&board));

    printf("launch this game? (y/n) : ");
    printf("\n> ");
    char key;
    do {
      key = _getch();
      if (key != 'y' && key != 'n') {
        print_err(INVALID_INPUT_ERROR);
        printf("\n> ");
      }
    } while (key != 'y' && key != 'n');

    if (key == 'y') {
      const char *game_board = build_board(get_board(&gs), DEFAULT_COLS,
                                           DEFAULT_SQUARE_LEN, BORDERS);

      wait_keypress("press to launch the game");
      game_loop(&pls, &board, game_board);

    } else {
      wait_keypress("press to go back to the menu");
    }

  } else {
    new_screen();
    printf("Many games found. ");
    int index = choose_save(gss);

    if (index == QUIT_GAME) {
      wait_keypress("press to go back to the menu");
    } else {

      GameState gs = *get_gamestate(&gss, index);
      Players pls = get_players(&gs);
      Board board = get_board(&gs);

      const char *game_board = build_board(get_board(&gs), DEFAULT_COLS,
                                           DEFAULT_SQUARE_LEN, BORDERS);

      wait_keypress("press to launch the game");
      game_loop(&pls, &board, game_board);
    }
  }

  logger.exit_fn();
}
