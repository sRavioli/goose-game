// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include <conio.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/globals.h"
#include "../inc/inputs.h"

#include "../common/inc/types/board.h"
#include "../common/inc/types/entry.h"
#include "../common/inc/types/gamestate.h"
#include "../common/inc/types/player.h"
#include "../common/inc/types/players.h"

#include "../common/inc/error.h"
#include "../common/inc/logger.h"
#include "../common/inc/math.h"
#include "../common/inc/string.h"
#include "../common/inc/term.h"

#include "../inc/handle_leaderboard.h"
#include "../inc/handle_saving.h"

#include "../inc/handle_game.h"
#include "../inc/private/handle_game.h"

static const char *BORDERS[8] = DEFAULT_BORDERS;

int ask_num_in_range(const int min, const int max, const char name[]) {
  // this function asks the user to input a number within a given range. It
  // keeps prompting the user until a valid number within the range is provided.

  logger.enter_fn(__func__);

  logger.log("asking val of %s in range [%i, %i]", name, min, max);
  int result;
  char buffer[MAX_BUFFER_LEN];
  int is_input_valid = FALSE;
  do {
    printf(ASK_BOUND_VALUE_FMT, name, min, max);
    fgets(buffer, sizeof(buffer), stdin);

    // remove the trailing newline character
    buffer[strcspn(buffer, "\n")] = '\0';

    // convert buffer to integer
    char *endptr;
    result = strtol(buffer, &endptr, DECIMAL_BASE);

    // check for conversion errors
    if (endptr == buffer || *endptr != STR_END) {
      logger.log("value %i is not a string, continuing", result);
      print_err(INVALID_INPUT_ERROR);
    } else if (result < min || result > max) {
      logger.log("value %i is out of bounds, continuing", result);
      print_err(VALUE_OUT_OF_BOUND_ERROR);
    } else {
      is_input_valid = TRUE;
    }
  } while (!is_input_valid);

  logger.log("value %i is inside bounds. returning", result);
  logger.exit_fn();
  return result;
}

void conform_username(char username[]) {
  // this function modifies the provided username by truncating it to a maximum
  // length, converting it to uppercase, and adding a filler character if the
  // length is less than the maximum allowed length.
  logger.enter_fn(__func__);
  logger.log("conforming given (%s) username", username);

  str_truncate(username, MAX_USERNAME_LENGTH);
  logger.log("truncated: %s", username);

  str_to_uppercase(username);
  logger.log("uppercased: %s", username);

  nconcat(username, FILLER_CHAR, MAX_USERNAME_LENGTH - strlen(username));

  logger.log("returning: %s", username);
  logger.exit_fn();
}

int is_username_valid(const char username[]) {
  // this function checks if a given username is valid. It scans through each
  // character of the username and returns FALSE if any punctuation or digit is
  // found. Otherwise, it returns TRUE.

  logger.enter_fn(__func__);
  logger.log("validating username '%s'", username);

  int i = 0;
  while (username[i]) {
    // scanf_s stops at first whitespace so no spaces in username
    if (ispunct(username[i]) || isdigit(username[i])) {
      logger.log("username '%s' is invalid", username);
      logger.exit_fn();
      return FALSE;
    }
    i = i + 1;
  }

  logger.log("username '%s' is valid", username);
  logger.exit_fn();
  return TRUE;
}

int find_duplicate_username(Players *pls, const char username[]) {
  // this function searches for any duplicate username. It scans all the
  // previous usernames and returns the index of the duplicate if found,
  // otherwise it will return INDEX_NOT_FOUND.

  logger.enter_fn(__func__);
  logger.log("searching for a duplicate username");
  int i = 0;
  while (i < get_players_num(pls)) {
    if (strcmp(get_username(get_player(pls, i)), username) == 0) {
      logger.log("found duplicate in position %i", i);
      logger.exit_fn();
      return i;
    }
    i = i + 1;
  }
  logger.log("no duplicate found");
  logger.exit_fn();
  return INDEX_NOT_FOUND;
}

char *ask_username(Players *pls, const int player_idx) {
  // this function asks the player to enter their username. It allocates memory
  // for the username, reads input from the user, checks if the username is
  // valid, and ensures the username conforms to the required format.
  logger.enter_fn(__func__);

  char *username = str_allocate(MAX_BUFFER_LEN);

  logger.log("asking player %i for username", player_idx);
  int valid = FALSE;
  while (!valid) {
    printf(ASK_USERNAME_FMT, player_idx);
    scanf_s("%s", username, MAX_BUFFER_LEN);
    getchar();

    conform_username(username);
    if (!is_username_valid(username)) {
      print_err(INVALID_USERNAME_ERROR);
    } else {
      int duplicate = find_duplicate_username(pls, username);
      if (duplicate != INDEX_NOT_FOUND) {
        print_err(DUPLICATE_USERNAME_ERROR);
      } else {
        printf(PRINT_VALID_USERNAME_FMT, username);
        logger.exit_fn();
        valid = TRUE;
      }
    }
  }
  printf("\n");

  logger.log("player %i username: %s. returning", player_idx, username);
  logger.exit_fn();
  return username;
}

Players *create_players(const int num_players) {
  // this function creates a Players struct. It allocates memory for it, calls
  // ask_username() to get the username for each user, sets all the default
  // values necessary to start a new game.
  logger.enter_fn(__func__);
  logger.log("asking players usernames");

  printf("%s", USERNAME_SCREEN_TITLE);

  // create the struct
  Players *pls = (Players *)malloc(sizeof(Players));  // NOLINT
  if (!pls) {
    logger.stop();
    throw_err(ALLOCATION_ERROR);
  }

  set_players_num(pls, num_players);
  // set_turn(pls, INITIAL_TURN);

  int i = 0;
  while (i < num_players) {
    Player *pl = (Player *)malloc(sizeof(Player));  // NOLINT
    if (!pl) {
      logger.stop();
      throw_err(ALLOCATION_ERROR);
    }

    char *username = ask_username(pls, i + 1);
    set_username(pl, username);
    free(username);

    set_id(pl);
    set_position(pl, INITIAL_POSITION);
    set_score(pl, INITIAL_SCORE);
    set_turns_blocked(pl, NO_TURNS_BLOCKED);

    logger.log("created player. username: %s, id: %i, pos: %i, score: %i, "
               "turns blocked: %i",
               get_username(pl), get_id(pl), get_position(pl), get_score(pl),
               get_turns_blocked(pl));

    set_player(pls, pl, i);
    free(pl);

    i = i + 1;
  }

  logger.log("created %i players", i);
  wait_keypress("press any key to continue");

  logger.exit_fn();
  return pls;
}

void selection_sort_players(Players *players, int *dice_rolls) {
  // this function uses selection sort to sort the players according to their
  // dice rolls.
  logger.enter_fn(__func__);
  logger.log("sorting players based on dice roll");

  int i = 0;
  while (i < get_players_num(players) - 1) {
    int max_idx = i;
    int j = i + 1;
    while (j < get_players_num(players)) {
      if (dice_rolls[j] > dice_rolls[max_idx]) {
        max_idx = j;
      }
      j = j + 1;
    }
    if (max_idx != i) {
      logger.log("swapping %s with %s", get_username(get_player(players, i)),
                 get_username(get_player(players, max_idx)));
      swap_int(&dice_rolls[i], &dice_rolls[max_idx]);
      swap_players(players, i, max_idx);
    }
    i = i + 1;
  }
  logger.exit_fn();
}

void interactive_roll(Players *pls, int *dice_rolls) {
  // this function makes each player roll dice interactively by asking to press
  // any key. It will then fill the given dice_rolls array.
  logger.enter_fn(__func__);
  logger.log("rolling dice for players");

  int i = 0;
  while (i < get_players_num(pls)) {
    const char *username = get_username(get_player(pls, i));
    wait_keypress(PRESS_TO_ROLL_FMT, username);

    dice_rolls[i] = roll_dice();
    clear_line();
    printf(ROLL_RESULT_FMT, username, dice_rolls[i]);
    logger.log("%s rolled a %i", username, dice_rolls[i]);

    i = i + 1;
  }
  printf("\n");
  logger.exit_fn();
}

void interactive_reroll(Players *pls, int *dice_rolls) {
  // this function makes players who have rolled the same number, re-roll dice
  // interactively by asking to press any key. It will then sort the players
  // accordingly.
  logger.enter_fn(__func__);
  logger.log("rerolling for players with duplicate rolls");

  int i = 0;
  while (i < get_players_num(pls) - 1) {
    int reroll_start = i;
    while (i < get_players_num(pls) - 1 && dice_rolls[i] == dice_rolls[i + 1]) {
      i = i + 1;
    }
    if (reroll_start != i) {
      printf("%s", DICE_TIE_MSG);

      // reroll
      logger.log("rerolling...");
      int j = reroll_start;
      while (j <= i) {
        const char *username = get_username(get_player(pls, j));
        wait_keypress(PRESS_TO_REROLL_FMT, username);

        dice_rolls[j] = roll_dice();
        clear_line();
        printf(REROLL_RESULT_FMT, username, dice_rolls[j]);
        logger.log(REROLL_RESULT_FMT, username, dice_rolls[j]);

        j = j + 1;
      }
      selection_sort_players(pls, dice_rolls);
      logger.log("players have been sorted");
    }
    i = i + 1;
  }
  printf("\n");
  logger.exit_fn();
}

void print_players_list(Players *pls) {
  // this function print the players in the order that has been decided by dice
  // rolls.
  logger.enter_fn(__func__);
  logger.log("printing player order");

  printf("%s", FINAL_ORDER_MSG);
  int i = 0;
  while (i < get_players_num(pls)) {
    printf("%s", get_username(get_player(pls, i)));
    if (i < get_players_num(pls) - 1) {
      printf(", ");
    }
    i = i + 1;
  }
  printf("\n\n");
  logger.exit_fn();
}

void sort_players_by_dice(Players *pls) {
  // this function sorts the players in the Players struct based on their dice
  // rolls. It rolls the dice for each player, assigns the dice values to their
  // dice_rolls array, sorts the players array using selection sort based on the
  // dice rolls, rerolls the dice for tied players, and prints the sorted list
  // of players and their final die values.
  logger.enter_fn(__func__);
  logger.log("sorting players based on their dice roll");

  logger.log("allocating memory for dice_rolls array");
  int *dice_rolls =
      (int *)malloc(get_players_num(pls) * sizeof(int));  // NOLINT

  printf("TURN ORDER\n\n");

  // roll dice for each player and assign to their dice_rolls array
  interactive_roll(pls, dice_rolls);

  // sort players array based on dice roll using selection sort
  selection_sort_players(pls, dice_rolls);

  // reroll dice for tied players until there are no more ties
  interactive_reroll(pls, dice_rolls);
  free(dice_rolls);

  // print the sorted list of players and their final die values
  print_players_list(pls);
  wait_keypress("Press any key to continue");
  logger.exit_fn();
}

int check_square(const Board *board, int position) {
  // this function checks the value of a square on the board and returns the
  // position to move to based on the square type.
  logger.enter_fn(__func__);
  logger.log("checking if square is of goose type");

  if (get_square(board, position) == GOOSE_VALUE) {
    logger.log("square is goose");
    logger.exit_fn();
    return position + 1;
  }

  logger.exit_fn();
  return position;
}

void insert_goose_squares(Board *board) {
  // this function inserts goose squares on the board at regular intervals.
  logger.enter_fn(__func__);
  logger.log("inserting goose squares");

  int i = GOOSE_SPACING - 1;
  while (i < get_dim(board) - 1) {
    logger.log("inserting square at pos %i", i);
    set_square(board, i, GOOSE_VALUE);
    i = i + GOOSE_SPACING;
  }
  logger.exit_fn();
}

void insert_special_squares(Board *board) {
  // this function inserts special squares (e.g., bridge, inn, well) on the
  // board at specific positions.
  logger.enter_fn(__func__);
  logger.log("inserting special squares");

  int special_poss[] = {BRIDGE_SQUARE,    INN_SQUARE,    WELL_SQUARE,
                        LABYRINTH_SQUARE, PRISON_SQUARE, SKELETON_SQUARE};
  int special_vals[] = {BRIDGE_VALUE,    INN_VALUE,    WELL_VALUE,
                        LABYRINTH_VALUE, PRISON_VALUE, SKELETON_VALUE};
  int num_special_squares = sizeof(special_poss) / sizeof(special_poss[0]);

  int i = 0;
  while (i < num_special_squares) {
    int special_pos =
        proportion(get_dim(board), special_poss[i], MAX_NUM_SQUARES);
    special_pos = check_square(board, special_pos);
    set_square(board, special_pos, special_vals[i]);
    logger.log("inserted square at pos %i", special_pos);
    i = i + 1;
  }
  logger.exit_fn();
}

Board *create_board(const int board_dim) {
  // creates a new game board with the specified dimensions. Initializes the
  // board with sequential values, inserts goose squares, and inserts special
  // squares.
  logger.enter_fn(__func__);
  logger.log("creating game board (array)");

  Board *board = (Board *)malloc(sizeof(Board));  // NOLINT
  set_dim(board, board_dim);

  logger.log("populating game board array");
  int i = 0;
  while (i < board_dim) {
    set_square(board, i, i + 1);
    i = i + 1;
  }

  insert_goose_squares(board);
  insert_special_squares(board);

  logger.exit_fn();
  return board;
}

char *build_border(const char *borders[4], const int square_len, const int cols,
                   const int rows, const int row, const Board board) {
  /* segments contains the four segments needed to create a border:
   * - west  0;
   * - east  1;
   * - join  2;
   * - dash  3.
   */
  logger.enter_fn(__func__);
  logger.log("attempting to build board border");

  char *buffer = alloc_char(borders[0], cols * square_len);
  char *ndash = alloc_char(borders[3], square_len - 1);
  nconcat(ndash, borders[3], square_len - 1);

  const int square_size = 1 + square_len * strlen(borders[0]);
  const int board_dim = get_dim(&board);

  int col = 0;
  while (col < cols) {
    if (row % 2 == 0) {
      int pos = row * cols + col;
      int is_last_of_row =
          ((col == cols - 1) && (row != rows - 1)) || (pos == board_dim - 1);

      if (col == 0) {                    // 1st sq of the row
        fconcat(buffer, square_size, "%s%s", borders[0], ndash);
      } else if (is_last_of_row) {       // last sq of the row
        fconcat(buffer, square_size, "%s%s", borders[2], ndash);
        concat(buffer, borders[1]);
      } else if (pos < board_dim - 1) {  // between 1st & last
        fconcat(buffer, square_size, "%s%s", borders[2], ndash);
      } else {                           // when traveling RtL
        fconcat(buffer, square_size, "%*s", square_len, "");
      }
    } else {
      int pos = (row + 1) * cols - col - 1;
      int is_fist = (col == 0) && (row != rows - 1);

      if (is_fist || pos == board_dim - 1) {  // 1st sq of the row and last sq
        fconcat(buffer, square_size, "%s%s", borders[0], ndash);
      } else if (col == cols - 1) {           // last sq of the row
        fconcat(buffer, square_size, "%s%s", borders[2], ndash);
        concat(buffer, borders[1]);
      } else if (pos < board_dim - 1) {       // between 1st & last
        fconcat(buffer, square_size, "%s%s", borders[2], ndash);
      } else {                                // when traveling LtR
        fconcat(buffer, square_size, "%*s", square_len, "");
      }
    }
    col = col + 1;
  }
  // add line end char since nothing should be present on the same line
  concat(buffer, LINE_END);

  logger.log("built game border");
  logger.exit_fn();
  return buffer;
}

char *sq_to_str(const int square) {
  logger.enter_fn(__func__);
  logger.log("converting square int to string");

  char *buffer = str_allocate((int)sizeof(square));  // NOLINT
  if (square == GOOSE_VALUE) {
    snprintf(buffer, sizeof(buffer), "%2s", "X2");
  } else if (square == BRIDGE_VALUE) {
    snprintf(buffer, sizeof(buffer), "%2s", "BR");
  } else if (square == INN_VALUE) {
    snprintf(buffer, sizeof(buffer), "%2s", "IN");
  } else if (square == WELL_VALUE) {
    snprintf(buffer, sizeof(buffer), "%2s", "WE");
  } else if (square == LABYRINTH_VALUE) {
    snprintf(buffer, sizeof(buffer), "%2s", "LA");
  } else if (square == PRISON_VALUE) {
    snprintf(buffer, sizeof(buffer), "%2s", "PR");
  } else if (square == SKELETON_VALUE) {
    snprintf(buffer, sizeof(buffer), "%2s", "SK");
  } else {
    snprintf(buffer, sizeof(buffer), "%2d", square);
  }

  logger.log("converted %i to '%s'", square, buffer);
  logger.exit_fn();
  return buffer;
}

char *build_squares(const char *vert, const int square_len, const int cols,
                    const int rows, const int row, const Board board) {
  logger.enter_fn(__func__);
  logger.log("attempting to build board squares");

  char *buffer = alloc_char(vert, cols * square_len);

  const int square_size = 1 + square_len * strlen(vert);
  const int board_dim = get_dim(&board);
  const int lspacing = (square_len - 3) / 2;
  int rspacing;
  if (square_len % 2 != 0) {
    rspacing = lspacing;
  } else {
    rspacing = lspacing + 1;
  }

  int col = 0;
  while (col < cols) {
    if (row % 2 == 0) {
      int pos = row * cols + col;
      int square = get_square(&board, pos);
      char *sq = sq_to_str(square);

      int is_fist = (col == cols - 1) && (row != rows - 1);
      int is_last = (pos == board_dim - 1) && (row == rows - 1);
      if (is_fist || is_last) {
        fconcat(buffer, square_size, "%s%*s%2s%*s%s", vert, lspacing, "", sq,
                rspacing, "", vert);
      } else if (pos < board_dim) {
        fconcat(buffer, square_size, "%s%*s%2s%*s", vert, lspacing, "", sq,
                rspacing, "");
      } else {
        fconcat(buffer, square_size, "%*s", square_len, "");
      }
    } else {
      int pos = (row + 1) * cols - col - 1;
      int square = get_square(&board, pos);
      char *sq = sq_to_str(square);

      if (col == cols - 1) {
        fconcat(buffer, square_size, "%s%*s%2s%*s%s", vert, lspacing, "", sq,
                rspacing, "", vert);
      } else if (pos < board_dim) {
        fconcat(buffer, square_size, "%s%*s%2s%*s", vert, lspacing, "", sq,
                rspacing, "");
      } else {
        fconcat(buffer, square_size, "%*s", square_len, "");
      }
    }
    col = col + 1;
  }
  // add line end char since nothing should be present on the same line
  concat(buffer, LINE_END);

  logger.log("built game squares");
  logger.exit_fn();
  return buffer;
}

char *build_board(const Board board, const int cols, const int square_len,
                  const char *borders[8]) {
  /* border chars will be in the following order:
   * - nw_corner  0  (ex. "┌");
   * - ne_corner  1  (ex. "┐");
   * - sw_corner  2  (ex. "└");
   * - se_corner  3  (ex. "┘");
   * - join_down  4  (ex. "┬");
   * - join_up    5  (ex. "┴");
   * - dash       6  (ex. "─");
   * - vert       7  (ex. "│").
   */
  logger.enter_fn(__func__);
  logger.log("building game board (visual)");

  int rows = (get_dim(&board) + cols - 1) / cols;  // calculate rows needed

  // char *game_board = alloc_char(borders[0], 3 * rows * cols * square_len);
  char *game_board =
      str_allocate(3 * rows * cols * square_len * sizeof(borders[0]));
  const char *top_borders[4] = {borders[0], borders[1], borders[4], borders[6]};
  const char *bot_borders[4] = {borders[2], borders[3], borders[5], borders[6]};
  const char *vert = borders[7];

  int row = 0;
  while (row < rows) {
    char *top = build_border(top_borders, square_len, cols, rows, row, board);
    char *squares = build_squares(vert, square_len, cols, rows, row, board);
    char *bot = build_border(bot_borders, square_len, cols, rows, row, board);

    const int source_size = 1 + strlen(top) + strlen(squares) + strlen(bot);
    logger.log("attempting to concatenate rows");
    fconcat(game_board, source_size, "%s%s%s", top, squares, bot);
    logger.log("concatenated rows");

    free(top);
    free(squares);
    free(bot);
    logger.log("memory freed");

    row = row + 1;
  }

  logger.exit_fn();
  return game_board;
}

void print_board(const char game_board[]) { printf("%s", game_board); }

int find_other_player_in_square(Players *pls, Player *curr_pl,
                                const int target_sq) {
  logger.enter_fn(__func__);
  logger.log("searching for another player in square %i", target_sq);

  int i = 0;
  while (i < get_players_num(pls)) {
    // check whether a player different than the given one is in the square

    if ((get_id(get_player(pls, i)) != get_id(curr_pl)) &&
        (get_position(get_player(pls, i)) == target_sq)) {
      logger.log("found player %s in square %i",
                 get_username(get_player(pls, i)), target_sq);
      logger.exit_fn();
      return i;
    }

    i = i + 1;
  }

  logger.log("no player has been found");
  logger.exit_fn();
  return INDEX_NOT_FOUND;
}

void update_score(Player *pl) {
  logger.enter_fn(__func__);
  logger.log("updating %s score", get_username(pl));
  set_score(pl, get_score(pl) + 1);
  logger.exit_fn();
}

int check_player_pos(Players *pls, Player *pl, Board *board, const int roll) {
  logger.enter_fn(__func__);
  logger.log("cheching player position");

  int current_sq = get_square(board, get_position(pl));
  int target_pos = roll + get_position(pl);
  int target_sq = get_square(board, target_pos);

  int turns_blocked = get_turns_blocked(pl);

  // player is blocked
  if (turns_blocked > NO_TURNS_BLOCKED) {
    logger.log("player is blocked");

    if (current_sq == INN_VALUE) {
      logger.exit_fn();
      set_turns_blocked(pl, get_turns_blocked(pl) - 1);
      printf("turns still blocked for the INN square : %d\n",
             get_turns_blocked(pl) + 1);
      return get_position(pl);
    }

    if ((current_sq == PRISON_VALUE || current_sq == WELL_VALUE) &&
        (roll == ESCAPE_ROLL1 || roll == ESCAPE_ROLL2)) {
      printf("\nThanks to your roll you are free now!\n");
      set_turns_blocked(pl, NO_TURNS_BLOCKED);
      logger.exit_fn();
      return get_position(pl);
    } else {
      printf("\nYou are blocked indefinitely\n");
      logger.exit_fn();
      return get_position(pl);
    }

    // player is free to move, check for special squares
  } else if (turns_blocked == NO_TURNS_BLOCKED) {
    // score has to be updated for each roll
    update_score(pl);

    logger.log("player is free to move");
    // check if player goes beyond the number of squares
    logger.log("bounds checking player pos");

    // check if the return position should be different than target_pos
    logger.log("checking for special cases");

    if (target_sq == GOOSE_VALUE || target_sq == BRIDGE_VALUE) {
      logger.log("player on goose or bridge square, double roll");
      logger.exit_fn();

      if (target_sq == GOOSE_VALUE) {
        printf("Landed on a GOOSE SQUARE: %s", GOOSE_TEXT);
      } else {
        printf("Landed on the BRIDGE SQUARE: %s", BRIDGE_TEXT);
      }
      if (((roll * 2) + get_position(pl)) < get_dim(board)) {
        logger.exit_fn();
        return ((roll * 2) + get_position(pl));
      } else {
        logger.exit_fn();
        return (get_dim(board) -
                (get_position(pl) + (roll * 2) - get_dim(board)));
      }

    } else if (target_sq == SKELETON_VALUE) {
      logger.log("player on skeleton square, back to start");
      logger.exit_fn();
      printf("Landed on the SKELETON SQUARE: %s", SKELETON_TEXT);
      return INITIAL_POSITION;

    } else if (target_sq == LABYRINTH_VALUE) {
      logger.log("player on labyrinth square");
      logger.exit_fn();
      printf("Landed on the LABYRINTH : ");
      printf(LABYRINTH_TEXT, (proportion(get_dim(board), LABYRINTH_DEFAULT_POS,
                                         MAX_NUM_SQUARES)) +
                                 1);
      return proportion(get_dim(board), LABYRINTH_DEFAULT_POS, MAX_NUM_SQUARES);

    } else if (target_sq == INN_VALUE) {
      logger.log("player on inn square");
      logger.exit_fn();
      printf("Landed on the INN : ");
      printf("%s", INN_TEXT);
      set_turns_blocked(pl, TURNS_BLOCKED_BY_INN);
      return target_pos;

    } else if (target_sq == PRISON_VALUE || target_sq == WELL_VALUE) {
      logger.log("checking if player is in prison/well");
      logger.log("player is in prison/well");

      if (target_sq == PRISON_VALUE) {
        printf("Landed on the PRISON : %s", PRISON_TEXT);
      } else {
        printf("Landed on the WELL : %s", WELL_TEXT);
      }

      set_turns_blocked(pl, INDEF_BLOCK);

      int other_pl_pos = find_other_player_in_square(pls, pl, target_pos);
      if (other_pl_pos != INDEX_NOT_FOUND) {  // INDEX_NOT_FOUND
        logger.log("found %s in prison, freeing them",
                   get_username(get_player(pls, other_pl_pos)));
        set_turns_blocked(get_player(pls, other_pl_pos), NO_TURNS_BLOCKED);
        logger.log("blocking player indefinetly");
        logger.exit_fn();
        printf("\n%s got out of prison thanks to %s that got in\n",
               get_username(get_player(pls, other_pl_pos)), get_username(pl));
        return target_pos;
      } else {
        logger.exit_fn();
        return target_pos;
      }
    } else {
      // player isn't on special square, return the roll + it's current position
      logger.log("no special case for player");
      logger.exit_fn();
      if (target_pos > get_dim(board)) {
        logger.log("player going out of bounds");
        logger.exit_fn();

        return ((get_dim(board)) - (target_pos - (get_dim(board))));
      } else {
        logger.exit_fn();
        return target_pos;
      }
    }
  }
}

void move_player(Players *pls, Player *pl, const int roll, Board *board) {
  logger.enter_fn(__func__);
  logger.log("moving %s based on it's roll %i", get_username(pl), roll);
  set_position(pl, check_player_pos(pls, pl, board, roll));
  logger.exit_fn();
}

int find_winner(Players *pls, Board *board) {
  logger.enter_fn(__func__);
  logger.log("searching for a winner");
  int i = 0;
  while (i < get_players_num(pls)) {
    int pos = get_position(get_player(pls, i)) + 1;
    if (pos == get_dim(board) || pos > get_dim(board)) {
      logger.log("found winner");
      logger.exit_fn();
      return i;
    }
    i = i + 1;
  }
  logger.log("no winner found");
  logger.exit_fn();
  return INDEX_NOT_FOUND;
}

void print_positions(Board *board, Players *pls) {
  logger.enter_fn(__func__);
  logger.log("printing player positions");

  printf("NAME\tPOS\n");
  int i = 0;
  while (i < get_players_num(pls)) {
    int sq = get_square(board, get_position(get_player(pls, i)));
    char *square = sq_to_str(sq);

    printf("%s\t", get_username(get_player(pls, i)));
    printf("%d ", 1 + get_position(get_player(pls, i)));
    printf("(%2s)\n", square);

    i = i + 1;
  }
  logger.exit_fn();
}

int pause_menu(Players *pls, Board *board, const char game_board[]) {
  logger.enter_fn(__func__);
  print_menu(PAUSE_MENU);

  int quit = FALSE;

  logger.log("waiting for a key");
  int display = TRUE;
  while (display) {
    char key = _getch();
    display = FALSE;

    if (key == 's') {
      logger.log("saving game");
      save_game(pls, board);
      wait_keypress("game saved, press any key to return to game...");
    } else if (key == 'l') {
      logger.log("exiting game");
      quit = TRUE;
    } else if (is_back_key(key)) {
      logger.log("returning to game");
    } else {
      logger.log("invalid key pressed, looping");
      print_err(INVALID_KEY_ERROR);
      display = TRUE;
    }
  }

  logger.exit_fn();
  return quit;
}

void game_loop(Players *pls, Board *board, const char game_board[]) {
  logger.enter_fn(__func__);
  logger.log("entering game loop");

  int quit_game = FALSE;
  while (!quit_game) {
    int i = 0;
    while (i < get_players_num(pls)) {
      new_screen();
      print_board(game_board);
      print_positions(board, pls);
      printf("\nTURN: %s", get_username(get_player(pls, i)));
      printf("\npress 'r' to roll, 'p' to pause game\n");
      logger.log("printed board (visual) and positions");

      logger.log("asking %s for keypress", get_username(get_player(pls, i)));
      int get_keypress = TRUE;
      while (get_keypress) {
        char keypress = _getch();
        get_keypress = FALSE;

        if (keypress == 'p') {
          logger.log("game paused");
          quit_game = pause_menu(pls, board, game_board);
        } else if (keypress == 'r') {
          logger.log("rolling dice");
          const int roll = roll_dice();
          printf("\n%s rolled a %d\n", get_username(get_player(pls, i)), roll);
          logger.log("%s rolled a %i", get_username(get_player(pls, i)), roll);

          move_player(pls, get_player(pls, i), roll, board);
          wait_keypress("press to continue...");

          logger.log("moved player");
        } else {
          clear_line();
          print_err(INVALID_KEY_ERROR);
          logger.log("invalid key, looping");
          get_keypress = TRUE;
        }
      }
      if (quit_game) {
        logger.log("returning to main menu");
        logger.exit_fn();
        return;
      }
      i = i + 1;
    }

    // search for a winner
    int winner_idx = find_winner(pls, board);
    if (winner_idx != INDEX_NOT_FOUND) {
      quit_game = TRUE;

      // add winner to the leaderboard
      Player pl = *get_player(pls, winner_idx);
      logger.log("winner is: %s", get_username(&pl));

      logger.log("creating entry for leaderboard");
      Entry winner;
      set_name(&winner, get_username(&pl));
      set_final_score(&winner, get_score(&pl));
      write_leaderboard(winner);

      new_screen();
      printf("Congratulations %s, you are the winner!\n", get_username(&pl));
      wait_keypress("press any key to return to main menu");
    }
  }
  logger.exit_fn();
  return;
}

void new_game() {
  logger.enter_fn(__func__);
  new_screen();

  // prepare for a new game
  int num_squares =
      ask_num_in_range(MIN_NUM_SQUARES, MAX_NUM_SQUARES, "squares");
  int num_players =
      ask_num_in_range(MIN_NUM_PLAYERS, MAX_NUM_PLAYERS, "players");

  Board *board = create_board(num_squares);
  Players *pls = create_players(num_players);

  const char *game_board =
      build_board(*board, DEFAULT_COLS, DEFAULT_SQUARE_LEN, BORDERS);

  new_screen();
  sort_players_by_dice(pls);

  new_screen();
  game_loop(pls, board, game_board);

  free(pls);
  free(board);

  logger.exit_fn();
}
