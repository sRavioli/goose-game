// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file board.h
 * @brief Header file for the @c Board struct and associated functions.
 *
 * This header file defines the @c Board struct, which represents a game board,
 * along with functions to manipulate the board, such as getting and setting
 * the value of a square, as well as getting and setting the dimension of the
 * board. It also defines all the constants associated with the @c Board type.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-07-11 19:39
 * @version 3.0
 * @copyright GNU GPLv3
 */

#ifndef BOARD_TYPE_H
#define BOARD_TYPE_H

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @defgroup BoardConstants Board Constants
 * @brief Constants related to the Board type.
 * @{
 */

/**
 * @defgroup BoardLimits Board Limits
 * @ingroup BoardConstants
 * @brief Limits associated with the Board type.
 * @{
 */

/**
 * @brief The minimum number of squares allowed on the board.
 */
#define MIN_NUM_SQUARES 50

/**
 * @brief The maximum number of squares allowed on the board.
 */
#define MAX_NUM_SQUARES 90
/** @} */  // End of BoardLimits

/**
 * @brief The spacing between goose squares on the board.
 */
#define GOOSE_SPACING 9

/**
 * @brief The value of a goose square on the board.
 */
#define GOOSE_VALUE 0

/**
 * @brief The position of the bridge square on the board.
 */
#define BRIDGE_SQUARE 6

/**
 * @brief The position of the inn square on the board.
 */
#define INN_SQUARE 19

/**
 * @brief The position of the well square on the board.
 */
#define WELL_SQUARE 31

/**
 * @brief The position of the labyrinth square on the board.
 */
#define LABYRINTH_SQUARE 42

/**
 * @brief The position of the prison square on the board.
 */
#define PRISON_SQUARE 52

/**
 * @brief The position of the skeleton square on the board.
 */
#define SKELETON_SQUARE 58

/**
 * @brief The value of the bridge square on the board.
 */
#define BRIDGE_VALUE -1

/**
 * @brief The value of the inn square on the board.
 */
#define INN_VALUE -2

#define TURNS_BLOCKED_BY_INN 3

/**
 * @brief The value of the well square on the board.
 */
#define WELL_VALUE -3

/**
 * @brief The value of the labyrinth square on the board.
 */
#define LABYRINTH_VALUE -4

#define LABYRINTH_DEFAULT_POS 33

/**
 * @brief The value of the prison square on the board.
 */
#define PRISON_VALUE -5

/**
 * @brief The value of the skeleton square on the board.
 */
#define SKELETON_VALUE -6

/**
 * @brief Text describing the effect of landing on a Goose square.
 *
 * After landing on a Goose square, the player should move forward a number of
 * squares equal to double the sum of the dice rolls.
 */
#define GOOSE_TEXT                                                             \
  "move forward a number of squares equal to double of those obtained by "     \
  "rolling the dice\n"

/**
 * @brief Text describing the effect of landing on an Inn square.
 *
 * After landing on an Inn square, the player is blocked from taking turns for 3
 * rounds.
 */
#define INN_TEXT "3 turns blocked\n"

/**
 * @brief Text describing the effect of landing on a Well square.
 *
 * After landing on a Well square, the player remains blocked until another
 * player arrives to take their place.
 */
#define WELL_TEXT                                                              \
  "remain blocked until another player arrives to take your place,or try to "  \
  "roll 5 or 7 in the next rounds\n"

/**
 * @brief Text describing the effect of landing on a Bridge square.
 *
 * After landing on a Bridge square, the player should move forward a number of
 * squares equal to double the sum of the dice rolls.
 */
#define BRIDGE_TEXT                                                            \
  "move forward a number of squares equal to double of those obtained by "     \
  "rolling the dice\n"

/**
 * @brief Text describing the effect of landing on a Labyrinth square.
 *
 * After landing on a Labyrinth square, the player should go back to a specific
 * square, which is indicated by the provided placeholder %d in the format
 * string.
 */
#define LABYRINTH_TEXT "go to square %d\n"  // 33 on the path from 90

/**
 * @brief Text describing the effect of landing on a Prison square.
 *
 * After landing on a Prison square, the player remains blocked until another
 * player arrives to take their place.
 */
#define PRISON_TEXT                                                            \
  "remain blocked until another player arrives to take your place,or try to "  \
  "roll 5 or 7 in the next rounds\n"

/**
 * @brief Text describing the effect of landing on a Skeleton square.
 *
 * After landing on a Skeleton square, the player should go back to the start
 * square.
 */
#define SKELETON_TEXT "go back to the start\n"

/**
 * @brief The default number of columns in the board.
 */
#define DEFAULT_COLS 15

/**
 * @brief The default length of a square on the board.
 */
#define DEFAULT_SQUARE_LEN 7

/**
 * @brief The default borders to use when printing the board.
 *
 * This is an array of eight strings that represent the characters to use for
 * the top-left, top-right, bottom-left, bottom-right, top, bottom, horizontal,
 * and vertical borders of each square, respectively.
 *
 * @warning This array should be assigned to another variable, eg:
 *          @code{.C}
 *          static const char *BORDERS[8] = DEFAULT_BORDERS;
 *          @endcode
 */
#define DEFAULT_BORDERS                                                        \
  { "+", "+", "+", "+", "+", "+", "-", "|" }
/** @} */  // End of BoardConstants

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief A struct representing a board for a game.
 *
 * This struct contains an array of integers called @c squares, which represents
 * the squares of the board, and an integer called @c dim, which represents the
 * dimensions of the board.
 *
 * @var int Board::squares
 * An array of integers representing the game board.
 *
 * @var Board::dim
 * An integer representing the dimensions of the board.
 */
typedef struct Board {
  int squares[MAX_NUM_SQUARES];  ///< An array of integers representing the
                                 ///< game board.
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

#endif  // !BOARD_TYPE_H
