// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "./board.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

int get_square(const Board *board, int position) {
  return board->squares[position];
}
void set_square(Board *board, int position, int value) {
  board->squares[position] = value;
}

int get_dim(const Board *board) { return board->dim; }
void set_dim(Board *board, int dimension) { board->dim = dimension; }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

char *sq_to_str(const int square) {
  char *buffer = alloc_char("cc", sizeof(square));
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

  return buffer;
}

char *build_border(const char *borders[4], const int square_len, const int cols,
                   const int rows, const int row, const Board board) {
  /* segments contains the four segments needed to create a border:
   * - west  0;
   * - east  1;
   * - join  2;
   * - dash  3.
   */
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

  return buffer;
}

char *build_squares(const char *vert, const int square_len, const int cols,
                    const int rows, const int row, const Board board) {
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
  int rows = (get_dim(&board) + cols - 1) / cols;  // calculate rows needed

  char *game_board = alloc_char(borders[0], 3 * rows * cols * square_len);
  const char *top_borders[4] = {borders[0], borders[1], borders[4], borders[6]};
  const char *bot_borders[4] = {borders[2], borders[3], borders[5], borders[6]};
  const char *vert = borders[7];

  int row = 0;
  while (row < rows) {
    char *top = build_border(top_borders, square_len, cols, rows, row, board);
    char *squares = build_squares(vert, square_len, cols, rows, row, board);
    char *bot = build_border(bot_borders, square_len, cols, rows, row, board);

    const int source_size = 1 + strlen(top) + strlen(squares) + strlen(bot);
    fconcat(game_board, source_size, "%s%s%s", top, squares, bot);

    free(top);
    free(squares);
    free(bot);

    row = row + 1;
  }

  return game_board;
}

void print_board(char *board) { printf("%s", board); }
