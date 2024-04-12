/**
 * @file board.h
 * @brief Header file for the @c Board struct and associated functions.
 *
 * This header file defines the @c Board struct, which represents a game board,
 * along with functions to manipulate the board, such as getting and setting
 * the value of a square, as well as getting and setting the dimension of the
 * board.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-05-05 16:02
 * @version 2.0
 * @copyright GNU GPLv3
 */

#ifndef BOARD_TYPE_H
#define BOARD_TYPE_H

#include "./string.h"

#include <stdio.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * @def MIN_NUM_SQUARES
 * @brief The minimum number of squares allowed on the board.
 */
#define MIN_NUM_SQUARES 50

/**
 * @def MAX_NUM_SQUARES
 * @brief The maximum number of squares allowed on the board.
 */
#define MAX_NUM_SQUARES 90

/**
 * @def GOOSE_SPACING
 * @brief The spacing between goose squares on the board.
 */
#define GOOSE_SPACING 9

/**
 * @def GOOSE_VALUE
 * @brief The value of a goose square on the board.
 */
#define GOOSE_VALUE 0

/**
 * @def BRIDGE_SQUARE
 * @brief The position of the bridge square on the board.
 */
#define BRIDGE_SQUARE 6

/**
 * @def INN_SQUARE
 * @brief The position of the inn square on the board.
 */
#define INN_SQUARE 19

/**
 * @def WELL_SQUARE
 * @brief The position of the well square on the board.
 */
#define WELL_SQUARE 31

/**
 * @def LABYRINTH_SQUARE
 * @brief The position of the labyrinth square on the board.
 */
#define LABYRINTH_SQUARE 42

/**
 * @def PRISON_SQUARE
 * @brief The position of the prison square on the board.
 */
#define PRISON_SQUARE 52

/**
 * @def SKELETON_SQUARE
 * @brief The position of the skeleton square on the board.
 */
#define SKELETON_SQUARE 58

/**
 * @def BRIDGE_VALUE
 * @brief The value of the bridge square on the board.
 */
#define BRIDGE_VALUE -1

/**
 * @def INN_VALUE
 * @brief The value of the inn square on the board.
 */
#define INN_VALUE -2

/**
 * @def WELL_VALUE
 * @brief The value of the well square on the board.
 */
#define WELL_VALUE -3

/**
 * @def LABYRINTH_VALUE
 * @brief The value of the labyrinth square on the board.
 */
#define LABYRINTH_VALUE -4

/**
 * @def PRISON_VALUE
 * @brief The value of the prison square on the board.
 */
#define PRISON_VALUE -5

/**
 * @def SKELETON_VALUE
 * @brief The value of the skeleton square on the board.
 */
#define SKELETON_VALUE -6

/**
 * @def DEFAULT_COLS
 * @brief The default number of columns in the board.
 */
#define DEFAULT_COLS 15

/**
 * @def DEFAULT_SQUARE_LEN
 * @brief The default length of a square on the board.
 */
#define DEFAULT_SQUARE_LEN 7

/**
 * @def DEFAULT_BORDERS
 * @brief The default borders to use when printing the board.
 *
 * This is an array of eight strings that represent the characters to use for
 * the top-left, top-right, bottom-left, bottom-right, top, bottom, horizontal,
 * and vertical borders of each square, respectively.
 *
 * @warning This array should be used as follows:
 *          @code
 *          const char *BORDERS[8] = DEFAULT_BORDERS;
 *          @endcode
 */
#define DEFAULT_BORDERS                                                        \
  { "╭", "╮", "╰", "╯", "┬", "┴", "─", "│" }

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * @brief A struct representing a board for a game.
 *
 * This struct contains an array of integers called @c squares, which represents
 * the state of the board, and an integer called @c dim, which represents the
 * dimensions of the board.
 *
 * @var int Board::squares
 * An array of integers representing the state of the board.
 *
 * @var Board::dim
 * An integer representing the dimensions of the board.
 */
typedef struct Board {
  int squares[MAX_NUM_SQUARES];  ///< An array of integers representing the
                                 ///< state of the board.
  int dim;  ///< An integer representing the dimensions of the board.
} Board;

/**
 * @brief Get the value of a square on the board.
 *
 * This function retrieves the value of a square on the board, given its
 * position.
 *
 * @param[in] board    Pointer to the @c Board struct.
 * @param[in] position Position of the square on the board.
 *
 * @return Value of the square at the given position.
 */
int get_square(const Board *board, int position);

/**
 * @brief Set the value of a square on the board.
 *
 * This function sets the value of a square on the board, given its position and
 * value.
 *
 * @param[in,out] board    Pointer to the @c Board struct.
 * @param[in]     position Position of the square on the board.
 * @param[in]     value    Value to set for the square.
 *
 * @return void.
 */
void set_square(Board *board, int position, int value);

/**
 * @brief Get the dimension of the board.
 *
 * This function retrieves the dimension of the board.
 *
 * @param[in] board Pointer to the @c Board struct.
 *
 * @return Dimension of the board.
 */
int get_dim(const Board *board);

/**
 * @brief Set the dimension of the board.
 *
 * This function sets the dimension of the board.
 *
 * @param[in,out] board     Pointer to the @c Board struct.
 * @param[in]     dimension Dimension to set for the board.
 *
 * @return void.
 */
void set_dim(Board *board, int dimension);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * @brief Build the game board as a string.
 *
 * This function takes a @c Board structure, along with other parameters, and
 * creates a string representation of the game board. The resulting string
 * includes the border characters specified in the @c borders array.
 *
 * @param[in] board      The @c Board structure to represent as a string
 * @param[in] cols       The number of columns in the game board
 * @param[in] square_len The length of one side of a square on the game board
 * @param[in] borders    An array of eight characters to use as the border
 *                       characters for the game board. The characters will be
 *                       used in the following order:
 *                       - nw_corner (ex. "┌")
 *                       - ne_corner (ex. "┐")
 *                       - sw_corner (ex. "└")
 *                       - se_corner (ex. "┘")
 *                       - join_down (ex. "┬")
 *                       - join_up (ex. "┴")
 *                       - dash (ex. "─")
 *                       - vert (ex. "│")
 * @return A string representation of the game board
 */
char *build_board(const Board board, const int cols, const int square_len,
                  const char *borders[8]);

/**
 * @brief Prints the game board to stdout.
 *
 * This function prints the provided game board to stdout using the @c printf()
 * function.
 *
 * @param board The game board to print.
 *
 * @return void.
 */
void print_board(char *board);

#endif  // !BOARD_TYPE_H
