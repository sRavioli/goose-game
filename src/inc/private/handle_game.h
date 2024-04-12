// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file private/game_module.h
 * @brief This file contains private functions and declarations related to the
 *        game module.
 *
 * The file includes necessary header files for board and player types from the
 * common module. It defines various helper functions used internally by the
 * game module to facilitate gameplay and manage game state.
 *
 * The functions in this file are responsible for tasks such as handling user
 * input, validating usernames, creating and managing players, sorting players
 * based on dice rolls, building and printing the game board, checking player
 * positions, updating scores, and determining the winner of the game.
 *
 * @note The functions in this file are intended for internal use within the
 *       game module and should not be accessed or called directly from outside
 *       the module.
 *
 * @warning Modifying or calling these functions without proper understanding of
 *          their implementation may result in unexpected behavior and errors in
 *          the game module.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-07-08 01:46
 * @version 2.0
 * @copyright GNU GPLv3
 */

#ifndef GAME_MODULE_PRIVATE_H
#define GAME_MODULE_PRIVATE_H

#include "../../common/inc/types/board.h"
#include "../../common/inc/types/players.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Asks the user to input a number within a given range.
 *
 * This function prompts the user to input a number within the specified range.
 * It keeps prompting the user until a valid number within the range is
 * provided.
 *
 * @param[in] min  The minimum value of the range.
 * @param[in] max  The maximum value of the range.
 * @param[in] name The name of the value being asked (e.g., "squares",
 *                 "players").
 *
 * @return The valid number input by the user within the specified range.
 */
int ask_num_in_range(const int min, const int max, const char name[]);

/**
 * @brief Modifies the provided username to conform to certain rules.
 *
 * This function modifies the provided username by truncating it to a maximum
 * length, converting it to uppercase, and adding a filler character if the
 * length is less than the maximum allowed length.
 *
 * @param[in,out] username The username to be conformed.
 *
 * @return void.
 */
void conform_username(char username[]);

/**
 * @brief Checks if a given username is valid.
 *
 * This function checks if the given username is valid by scanning through each
 * character of the username. It returns `FALSE` if any punctuation or digit is
 * found, indicating an invalid username. Otherwise, it returns `TRUE`.
 *
 * @param[in] username The username to be validated.
 *
 * @return `TRUE` if the username is valid, `FALSE` otherwise.
 */
int is_username_valid(const char username[]);

/**
 * @brief Searches for a duplicate username.
 *
 * This function searches for any duplicate username by scanning all the
 * previous usernames stored in the Players structure. It returns the index of
 * the duplicate if found, otherwise it returns `INDEX_NOT_FOUND`.
 *
 * @param[in] pls      The Players structure containing the player information.
 * @param[in] username The username to search for.
 *
 * @return The index of the duplicate username if found, `INDEX_NOT_FOUND`
 *         otherwise.
 */
int find_duplicate_username(Players *pls, const char username[]);

/**
 * @brief Asks the player to enter their username.
 *
 * This function prompts the player with the specified index to enter their
 * username. It allocates memory for the username, reads input from the user,
 * checks if the username is valid, and ensures the username conforms to the
 * required format. The function returns the validated username.
 *
 * @param[in] pls        The Players structure containing the player
 *                       information.
 * @param[in] player_idx The index of the player for whom the username is being
 *            asked.
 *
 * @return The validated username entered by the player.
 */
char *ask_username(Players *pls, const int player_idx);

/**
 * @brief Creates a Players struct and initializes player information.
 *
 * This function creates a Players struct, allocates memory for it, and
 * initializes the player information by calling `ask_username()` to get the
 * username for each player. It sets all the default values necessary to start a
 * new game, such as player ID, position, score, and turns blocked. The function
 * returns the created Players struct.
 *
 * @param[in] num_players The number of players in the game.
 *
 * @return The created Players struct.
 */
Players *create_players(const int num_players);

/**
 * @brief Sorts the players based on their dice rolls using selection sort.
 *
 * This function sorts the players in the Players struct based on their dice
 * rolls, in descending order. It uses the selection sort algorithm to perform
 * the sorting.
 *
 * @param[in]     players    The Players struct containing the player
 *                           information.
 * @param[in,out] dice_rolls The array of dice rolls corresponding to each
 * player.
 *
 * @return void.
 */
void selection_sort_players(Players *players, int *dice_rolls);

/**
 * @brief Makes each player roll the dice interactively.
 *
 * This function makes each player in the Players struct roll the dice
 * interactively. It prompts the player to press any key to roll the dice and
 * stores the resulting dice roll in the provided `dice_rolls` array.
 *
 * @param[in]     pls The Players struct containing the player information.
 * @param[in,out] dice_rolls The array to store the dice rolls for each player.
 *
 * @return void.
 */
void interactive_roll(Players *pls, int *dice_rolls);

/**
 * @brief Performs interactive re-roll for players with duplicate dice rolls.
 *
 * This function makes players who have rolled the same number re-roll the dice
 * interactively. It prompts the players with duplicate rolls to press any key
 * to re-roll the dice and stores the resulting dice rolls in the provided
 * `dice_rolls` array. It then sorts the players accordingly based on the new
 * dice rolls.
 *
 * @param[in]     pls        The Players struct containing the player *
 *                           information.
 * @param[in,out] dice_rolls The array of dice rolls corresponding to each
 *                           player.
 *
 * @return void.
 */
void interactive_reroll(Players *pls, int *dice_rolls);

/**
 * @brief Prints the list of players in the order decided by dice rolls.
 *
 * This function prints the list of players in the order that has been decided
 * by the dice rolls. It retrieves the player information from the Players
 * struct and prints their usernames separated by commas.
 *
 * @param[in] pls The Players struct containing the player information.
 *
 * @return void.
 */
void print_players_list(Players *pls);

/**
 * @brief Sorts the players based on their dice rolls.
 *
 * This function sorts the players in the Players struct based on their dice
 * rolls. It rolls the dice for each player, assigns the dice values to their
 * dice_rolls array, sorts the players array using selection sort based on the
 * dice rolls, rerolls the dice for tied players, and prints the sorted list of
 * players and their final dice values.
 *
 * @param[in] pls The Players struct containing the player information.
 *
 * @return void.
 */
void sort_players_by_dice(Players *pls);

/**
 * @brief Checks the value of a square on the board and determines the position
 *        to move to.
 *
 * This function checks the value of a square on the board at the given
 * position. If the square is a goose square, it returns the position
 * incremented by 1, indicating that the player should move to the next square.
 * Otherwise, it returns the original position.
 *
 * @param[in] board    The Board struct representing the game board.
 * @param[in] position The current position of the player.
 *
 * @return The position to move to based on the square type.
 */
int check_square(const Board *board, int position);

/**
 * @brief Inserts goose squares on the board at regular intervals.
 *
 * This function inserts goose squares on the board at regular intervals
 * specified by the GOOSE_SPACING constant. It modifies the board by setting the
 * square values to the GOOSE_VALUE.
 *
 * @param[in,out] board The Board struct representing the game board.
 *
 * @return void.
 */
void insert_goose_squares(Board *board);

/**
 * @brief Inserts special squares on the board at specific positions.
 *
 * This function inserts special squares, such as bridge, inn, well, labyrinth,
 * prison, and skeleton, on the board at specific positions. It modifies the
 * board by setting the square values to the corresponding special values.
 *
 * @param[in,out] board The Board struct representing the game board.
 *
 * @return void.
 */
void insert_special_squares(Board *board);

/**
 * @brief Creates a new game board with the specified dimensions.
 *
 * This function creates a new game board with the specified dimensions. It
 * initializes the board with sequential values, inserts goose squares, and
 * inserts special squares (such as bridge, inn, well, labyrinth, prison, and
 * skeleton) at specific positions.
 *
 * @param[in] board_dim The dimensions of the game board.
 *
 * @return A pointer to the created Board struct representing the game board.
 */
Board *create_board(const int board_dim);

/**
 * @brief Builds the border of the game board at a specific row.
 *
 * This function builds the border of the game board at a specific row. It
 * constructs the border using the provided border characters and fills the
 * spaces between squares with dashes. The resulting border is returned as a
 * string.
 *
 * @param[in] borders    The array of border characters for different segments
 *                       of the border.
 * @param[in] square_len The length of each square.
 * @param[in] cols       The number of columns in the game board.
 * @param[in] rows       The number of rows in the game board.
 * @param[in] row        The current row for which the border is being built.
 * @param[in] board      The Board struct representing the game board.
 *
 * @return The built border of the game board as a string.
 */
char *build_border(const char *borders[4], const int square_len, const int cols,
                   const int rows, const int row, const Board board);

/**
 * @brief Converts a square value to a string representation.
 *
 * This function converts a square value to a string representation. It checks
 * for special square values (such as goose, bridge, inn, well, labyrinth,
 * prison, and skeleton) and returns the corresponding strings. For other square
 * values, it converts the integer value to a string.
 *
 * @param[in] square The square value to convert.
 *
 * @return The string representation of the square value.
 */
char *sq_to_str(const int square);

/**
 * @brief Builds the squares of the game board at a specific row.
 *
 * This function builds the squares of the game board at a specific row. It
 * retrieves the square values from the Board struct and converts them to string
 * representations. The squares are then filled with the corresponding strings,
 * separated by vertical border characters. The resulting squares are returned
 * as a string.
 *
 * @param[in] vert       The vertical border character.
 * @param[in] square_len The length of each square.
 * @param[in] cols       The number of columns in the game board.
 * @param[in] rows       The number of rows in the game board.
 * @param[in] row        The current row for which the squares are being built.
 * @param[in] board      The Board struct representing the game board.
 *
 * @return The built squares of the game board as a string.
 */
char *build_squares(const char *vert, const int square_len, const int cols,
                    const int rows, const int row, const Board board);

/**
 * @brief Prints the game board.
 *
 * This function prints the game board by outputting the provided game board
 * string.
 *
 * @param[in] game_board The string representing the game board.
 *
 * @return void.
 */
void print_board(const char game_board[]);

/**
 * @brief Finds another player in the same square.
 *
 * This function searches for another player in the same square as the target
 * square. It iterates through all the players and checks if any player other
 * than the current player is in the target square. If a player is found, the
 * index of the player is returned; otherwise, INDEX_NOT_FOUND is returned.
 *
 * @param[in] pls       The Players struct containing all the players.
 * @param[in] curr_pl   The current player.
 * @param[in] target_sq The target square to check.
 *
 * @return The index of the other player in the square, or INDEX_NOT_FOUND if no
 *         other player is found.
 */
int find_other_player_in_square(Players *pls, Player *curr_pl,
                                const int target_sq);

/**
 * @brief Updates the score of a player.
 *
 * This function updates the score of a player by incrementing it by 1.
 *
 * @param[in] pl   The player whose score needs to be updated.
 *
 * @return void.
 */
void update_score(Player *pl);

/**
 * @brief Checks the position of a player after a roll.
 *
 * This function checks the position of a player after a roll on the game board.
 * It considers various scenarios, such as the player being blocked, landing on
 * special squares, and going beyond the board dimensions. It updates the
 * player's score accordingly and returns the new position of the player.
 *
 * @param[in] pls   The Players struct containing all the players.
 * @param[in] pl    The player whose position needs to be checked.
 * @param[in] board The Board struct representing the game board.
 * @param[in] roll  The roll value.
 *
 * @return The new position of the player after the roll.
 */
int check_player_pos(Players *pls, Player *pl, Board *board, const int roll);

/**
 * @brief Moves a player based on their roll.
 *
 * This function moves a player based on their roll value. It updates the
 * player's position by calling the `check_player_pos` function and passing the
 * necessary parameters.
 *
 * @param[in] pls   The Players struct containing all the players.
 * @param[in] pl    The player to move.
 * @param[in] roll  The roll value.
 * @param[in] board The Board struct representing the game board.
 *
 * @return void.
 */
void move_player(Players *pls, Player *pl, const int roll, Board *board);

/**
 * @brief Finds the winner of the game.
 *
 * This function searches for the winner of the game by checking if any player
 * has reached or surpassed the board dimensions. It iterates through all the
 * players and checks their positions. If a player is found to have reached or
 * surpassed the board dimensions, the index of the player is returned;
 * otherwise, INDEX_NOT_FOUND is returned.
 *
 * @param[in] pls   The Players struct containing all the players.
 * @param[in] board The Board struct representing the game board.
 *
 * @return The index of the winner, or INDEX_NOT_FOUND if no winner is found.
 */
int find_winner(Players *pls, Board *board);

/**
 * @brief Prints the positions of all players on the game board.
 *
 * This function prints the positions of all players on the game board.
 * It iterates through all the players, retrieves their positions, and converts
 * them to square strings using the `sq_to_str()` function. The player name,
 * position, and square value are printed for each player.
 *
 * @param[in] board The Board struct representing the game board.
 * @param[in] pls   The Players struct containing all the players.
 *
 * @return void.
 */
void print_positions(Board *board, Players *pls);

/**
 * @brief Displays the pause menu and handles user input for navigating the
 *        menu.
 *
 * The pause menu is displayed to the user and waits for a key press. The
 * function reads the user's input and performs actions based on the entered
 * key.
 *
 * Available options:
 * - 's': Saves the game.
 * - 'l': Exits the main menu.
 * - 'b': Returns to the game.
 *
 * @note This function relies on the following helper functions:
 *       - `save_game(Players *pls, Board *board, const char game_board[])`:
 *          Saves the game.
 *       - `exit_game()`: Exits the game.
 *
 * @note The function ignores the backspace key if pressed.
 *
 * @param[in] pls        The Players struct containing all the players.
 * @param[in] board      The Board struct representing the game board.
 * @param[in] game_board The string representation of the game board.
 *
 * @return A boolean value indicating whether the game should quit (`TRUE`) or
 *         continue (`FALSE`).
 */
int pause_menu(Players *pls, Board *board, const char game_board[]);

#endif  // !GAME_MODULE_PRIVATE_H
