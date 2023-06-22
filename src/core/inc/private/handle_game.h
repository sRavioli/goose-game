// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef PRIVATE_GAME_MODULE_H
#define PRIVATE_GAME_MODULE_H

#include "../../../types/inc/board.h"
#include "../../../types/inc/players.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Asks the user to input a number within a given range.
 *
 * This function prompts the user to input a number within the specified range
 * [min, max]. It keeps prompting the user until a valid number within the range
 * is provided.
 *
 * @param[in] min  The minimum value of the range.
 * @param[in] max  The maximum value of the range.
 * @param[in] name The name of the value being asked for.
 *
 * @return The valid number input by the user within the range [min, max].
 */
int ask_num_in_range(const int min, const int max, const char name[]);

/**
 * @brief Modifies the provided username to conform to certain rules.
 *
 * This function modifies the provided username by truncating it to a maximum
 * length, converting it to uppercase, and adding a filler character if the
 * length is less than the maximum allowed length.
 *
 * @param[in,out] username The username to be modified.
 *
 * @return void.
 */
void conform_username(char username[]);

/**
 * @brief Checks if a given username is valid.
 *
 * This function checks if a given username is valid. It scans through each
 * character of the username and returns FALSE if any punctuation or digit is
 * found. Otherwise, it returns TRUE.
 *
 * @param[in] username The username to be validated.
 *
 * @return `TRUE` if the username is valid, `FALSE` otherwise.
 */
int is_username_valid(const char username[]);

/**
 * @brief Searches for a duplicate username.
 *
 * This function searches for any duplicate username. It scans all the previous
 * usernames and returns the index of the duplicate if found, otherwise it will
 * return INDEX_NOT_FOUND.
 *
 * @param[in] pls      The Players struct containing the usernames.
 * @param[in] username The username to search for.
 *
 * @return The index of the duplicate username if found, otherwise
 *         `INDEX_NOT_FOUND`.
 */
int find_duplicate_username(Players *pls, const char username[]);

/**
 * @brief Asks the player to enter their username.
 *
 * This function asks the player to enter their username. It allocates memory
 * for the username, reads input from the user, checks if the username is valid,
 * and ensures the username conforms to the required format.
 *
 * @param[in] pls        The Players struct containing the usernames of other
 *                       players.
 * @param[in] player_idx The index of the current player.
 *
 * @return The entered username.
 */
char *ask_username(Players *pls, const int player_idx);

/**
 * @brief Creates a Players struct and initializes player information.
 *
 * This function creates a Players struct. It allocates memory for it and sets
 * all the default values necessary to start a new game. It asks each player for
 * their username using the `ask_username` function.
 *
 * @param[in] num_players The number of players.
 *
 * @return The created Players struct.
 */
Players *create_players(const int num_players);

/**
 * @brief Frees memory allocated for the Players struct and associated
 * resources.
 *
 * This function frees memory allocated for the Players struct and associated
 * resources, such as the usernames of each player.
 *
 * @param[in] pls The Players struct to be destroyed.
 *
 * @return void.
 */
void destroy_players(Players *pls);

/**
 * @brief Sorts the players in the Players struct based on their dice rolls
 * using selection sort.
 *
 * This function uses the selection sort algorithm to sort the players in the
 * Players struct based on their dice rolls. It iterates over the players and
 * their corresponding dice rolls, finding the player with the maximum dice roll
 * and swapping their positions with the current player being considered. The
 * sorting is done in descending order, so the player with the highest dice roll
 * will be at the beginning of the Players struct.
 *
 * @param[in,out] players    The Players struct containing the player
 *                           information.
 * @param[in]     dice_rolls The array of dice rolls for each player.
 *
 * @return void.
 */
void selection_sort_players(Players *players, int *dice_rolls);

/**
 * @brief Allows each player to roll the dice interactively and stores the dice
 * rolls.
 *
 * This function facilitates an interactive dice roll for each player in the
 * Players struct. It prompts each player to press any key to roll the dice and
 * then stores the resulting dice roll in the provided dice_rolls array.
 *
 * @param[in]  pls        The Players struct containing the player information.
 * @param[out] dice_rolls The array to store the dice rolls for each player.
 *
 * @return void.
 */
void interactive_roll(Players *pls, int *dice_rolls);

/**
 * @brief Allows tied players to reroll the dice interactively and sorts the
 * players accordingly.
 *
 * This function handles the case where multiple players have rolled the same
 * number on the dice. It prompts the tied players to press any key to reroll
 * the dice and then stores the resulting dice rolls in the provided dice_rolls
 * array. After rerolling, it sorts the players in the Players struct based on
 * the updated dice rolls.
 *
 * @param[in,out] pls        The Players struct containing the player
 *                           information.
 * @param[in,out] dice_rolls The array of dice rolls for each player.
 *
 * @return void.
 */
void interactive_reroll(Players *pls, int *dice_rolls);

/**
 * @brief Prints the final order of players based on their dice rolls.
 *
 * This function prints the final order of players based on their dice rolls.
 * It retrieves the usernames of the players from the Players struct and prints
 * them in the order determined by the dice rolls. The usernames are separated
 * by commas, and the final order is displayed as a message.
 *
 * @param[in] pls The Players struct containing the player information.
 *
 * @return void.
 */
void print_players_list(Players *pls);

/**
 * @brief Sorts the players in the Players struct based on their dice rolls,
 * rerolls tied players, and prints the final order.
 *
 * This function sorts the players in the Players struct based on their dice
 * rolls. It rolls the dice for each player, assigns the dice values to their
 * dice_rolls array, sorts the players array using selection sort based on the
 * dice rolls, rerolls the dice for tied players, and finally prints the sorted
 * list of players and their final die values.
 *
 * @param[in,out] pls The Players struct containing the player information.
 *
 * @return void.
 */
void sort_players_by_dice(Players *pls);

/**
 * @brief Checks the value of a square on the board and returns the position to
 * move to based on the square type.
 *
 * This function checks the value of a square on the board and determines the
 * position to move to based on the square type. If the square value is equal to
 * the GOOSE_VALUE, the position will be incremented by one. Otherwise, the
 * position remains unchanged.
 *
 * @param[in] board    The Board struct containing the game board information.
 * @param[in] position The current position on the board.
 *
 * @return The position to move to based on the square type.
 */
int check_square(const Board *board, int position);

/**
 * @brief Inserts goose squares on the board at regular intervals.
 *
 * This function inserts goose squares on the board at regular intervals defined
 * by the GOOSE_SPACING constant. It starts from the index GOOSE_SPACING - 1 and
 * iterates over the board, setting the square value to GOOSE_VALUE at each
 * interval. This function modifies the board in place.
 *
 * @param[in,out] board The Board struct containing the game board information.
 *
 * @return void.
 */
void insert_goose_squares(Board *board);

/**
 * @brief Inserts special squares (e.g., bridge, inn, well) on the board at
 * specific positions.
 *
 * This function inserts special squares on the game board at predetermined
 * positions. The positions and corresponding values for the special squares are
 * defined in the 'special_poss' and 'special_vals' arrays respectively. The
 * function iterates over the special squares array, checks and adjusts the
 * position if necessary using the 'check_square' function, and then sets the
 * square value on the board using the 'set_square' function.
 *
 * @param[in,out] board The Board struct containing the game board information.
 *
 * @return void.
 */
void insert_special_squares(Board *board);

/**
 * @brief Creates a new game board with the specified dimensions.
 *
 * This function creates a new game board with the specified dimensions. It
 * initializes the board with sequential values, inserts goose squares, and
 * inserts special squares using the 'insert_goose_squares' and
 * 'insert_special_squares' functions respectively. The function dynamically
 * allocates memory for the board and returns a pointer to it.
 *
 * @param[in] board_dim The dimensions of the game board.
 *
 * @return A pointer to the created Board struct.
 */
Board *create_board(const int board_dim);

/**
 * @brief Builds the border segment of a game board row.
 *
 * This function builds the border segment of a game board row. It takes the
 * border characters as input and constructs the border segment based on the
 * specified conditions. The resulting border segment is stored in a character
 * buffer and returned.
 *
 * @param[in] borders    The array of border characters for constructing the
 *                       segment.
 * @param[in] square_len The length of each square in the game board.
 * @param[in] cols       The number of columns in the game board.
 * @param[in] rows       The number of rows in the game board.
 * @param[in] row        The current row being constructed.
 * @param[in] board      The Board struct containing the game board information.
 *
 * @return The constructed border segment as a character buffer.
 */
char *build_border(const char *borders[4], const int square_len, const int cols,
                   const int rows, const int row, const Board board);

/**
 * @brief Converts a square value to its corresponding string representation.
 *
 * This function converts a square value to its corresponding string
 * representation. It checks the value against predefined special square values
 * (e.g., goose, bridge, inn) and returns the appropriate string representation.
 * If the value is a normal square, it converts it to a string using 'snprintf'
 * and returns it.
 *
 * @param[in] square The square value to convert.
 *
 * @return The string representation of the square value.
 */
char *sq_to_str(const int square);

/**
 * @brief Builds the squares segment of a game board row.
 *
 * This function builds the squares segment of a game board row. It takes the
 * vertical border character and the game board's dimensions as input. The
 * function iterates over each square in the row, retrieves its value from the
 * board, converts it to a string representation using the 'sq_to_str' function,
 * and constructs the segment based on the specified conditions. The resulting
 * squares segment is stored in a character buffer and returned.
 *
 * @param[in] vert       The vertical border character.
 * @param[in] square_len The length of each square in the game board.
 * @param[in] cols       The number of columns in the game board.
 * @param[in] rows       The number of rows in the game board.
 * @param[in] row        The current row being constructed.
 * @param[in] board      The Board struct containing the game board information.
 *
 * @return The constructed squares segment as a character buffer.
 */
char *build_squares(const char *vert, const int square_len, const int cols,
                    const int rows, const int row, const Board board);

/**
 * @brief Builds the complete game board.
 *
 * This function builds the complete game board by combining the border and
 * squares segments. It takes the Board struct, the number of columns, the
 * square length, and the border characters as input. The function iterates over
 * each row in the board, calls the 'build_border' and 'build_squares' functions
 * to construct the corresponding segments, and concatenates them to form the
 * complete game board. The resulting game board is stored in a character buffer
 * and returned.
 *
 * @param[in] board      The Board struct containing the game board information.
 * @param[in] cols       The number of columns in the game board.
 * @param[in] square_len The length of each square in the game board.
 * @param[in] borders    The array of border characters for constructing the
 *                       board.
 *
 * @return The constructed game board as a character buffer.
 */
char *build_board(const Board board, const int cols, const int square_len,
                  const char *borders[8]);

/**
 * @brief Prints the game board.
 *
 * This function prints the game board to the console.
 *
 * @param[in] game_board The game board to be printed.
 *
 * @return void.
 */
void print_board(const char game_board[]);

/**
 * @brief Finds the index of another player in a specific square.
 *
 * This function searches for a player, different from the given current player,
 * in the specified square. It iterates over all the players in the Players
 * struct, checks their IDs and positions, and returns the index of the player
 * found. If no player is found in the square, it returns the constant value
 * INDEX_NOT_FOUND.
 *
 * @param[in] pls       The Players struct containing information about the
 *                      players.
 * @param[in] curr_pl   The current player.
 * @param[in] target_sq The target square to search for another player.
 *
 * @return The index of the other player found in the square, or INDEX_NOT_FOUND
 *         if no player is found.
 */
int find_other_player_in_square(Players *pls, Player *curr_pl,
                                const int target_sq);

/**
 * @brief Updates the score of a player based on the roll value.
 *
 * This function updates the score of a player by adding the product of the roll
 * value and 10 to the current score.
 *
 * @param[in,out] pl   The player whose score is updated.
 * @param[in]     roll The roll value used to calculate the score increment.
 *
 * @return void.
 */
void update_score(Player *pl, const int roll);

/**
 * @brief Checks the position of a player after rolling the dice.
 *
 * This function checks the position of a player after rolling the dice. It
 * takes into account the current position, the roll value, the game board, and
 * the special square conditions to determine the new position of the player. It
 * updates the score of the player, handles special square effects (e.g.,
 * prison, well), and returns the target position after considering the player's
 * movement and special squares.
 *
 * @param[in] pls   The Players struct containing information about the players.
 * @param[in] pl    The player whose position is being checked.
 * @param[in] board The Board struct containing the game board information.
 * @param[in] roll  The value rolled on the dice.
 *
 * @return The target position of the player after considering movement and
 *         special squares.
 */
int check_player_pos(Players *pls, Player *pl, Board *board, const int roll);

/**
 * @brief Moves a player on the game board based on the roll value.
 *
 * This function moves a player on the game board based on the roll value. It
 * calls the 'check_player_pos' function to determine the new position of the
 * player, and updates the player's position accordingly.
 *
 * @param[in]     pls   The Players struct containing information about the
 *                      players.
 * @param[in,out] pl    The player to be moved.
 * @param[in]     roll  The value rolled on the dice.
 * @param[in]     board The Board struct containing the game board information.
 *
 * @return void.
 */
void move_player(Players *pls, Player *pl, const int roll, Board *board);

/**
 * @brief Finds the index of the winner player.
 *
 * This function searches for the index of the winner player in the game. It
 * iterates over all the players in the Players struct, checks their positions,
 * and returns the index of the player who has reached the last square on the
 * game board. If no player has won yet, it returns the constant value
 * INDEX_NOT_FOUND.
 *
 * @param[in] pls   The Players struct containing information about the players.
 * @param[in] board The Board struct containing the game board information.
 *
 * @return The index of the winner player, or INDEX_NOT_FOUND if no winner is
 *         found yet.
 */
int find_winner(Players *pls, Board *board);

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Prints the positions of all players.
 *
 * This function prints the names and positions of all players in the provided
 * Players struct. It iterates over the players, retrieves their usernames and
 * positions, and prints them in a tabular format.
 *
 * @param[in] pls The Players struct containing information about the players.
 *
 * @return void.
 */
void print_positions(Players *pls);

/**
 * @brief Prints the positions of all players with additional debug information.
 *
 * This function prints the names, positions, and corresponding squares of all
 * players in the provided Players struct. It retrieves the square information
 * from the game board using the Board struct and prints it along with the
 * player's name and position. This function is intended for debugging purposes.
 *
 * @param[in] board The Board struct containing the game board information.
 * @param[in] pls   The Players struct containing information about the players.
 *
 * @return void.
 */
void dev_print_positions(Board *board, Players *pls);

/**
 * @brief Displays the pause menu and handles user input.
 *
 * This function displays the pause menu options and waits for user input. It
 * handles the 's' key (save game), 'l' key (leave game), and the back key
 * (resume game). Based on the user's input, it performs the corresponding
 * actions such as saving the game, leaving the game, or resuming the game.
 *
 * @param[in,out] quit       A pointer to the flag indicating whether to quit
 *                           the game.
 * @param[in]     pls        The Players struct containing information about the
 *                           players.
 * @param[in]     board      The Board struct containing the game board
 *                           information.
 * @param[in]     game_board The string representation of the game board.
 *
 * @return void.
 */
void pause_menu(int *quit, Players *pls, Board *board, const char game_board[]);

/**
 * @brief Runs the game loop and controls the game flow.
 *
 * This function runs the game loop and controls the game flow. It iterates over
 * the players in the Players struct and performs the following actions for each
 * player: displays the game board, prints player positions, prompts the player
 * to roll the dice, moves the player based on the roll, and checks for a
 * winner. If a winner is found, it displays the winner and ends the game.
 *
 * @param[in] pls        The Players struct containing information about the
 *                       players.
 * @param[in] board      The Board struct containing the game board information.
 * @param[in] game_board The string representation of the game board.
 *
 * @return void.
 */
void dev_game_loop(Players *pls, Board *board, const char game_board[]);

/**
 * @brief Frees memory and leaves the game.
 *
 * This function frees the memory pointed to by the provided pointer and any
 * additional pointers passed as variadic arguments. It is used to clean up
 * resources and terminate the game. The function iterates over the pointers,
 * starting from the initial pointer, and frees the memory associated with each
 * pointer until a NULL pointer is encountered.
 *
 * @param[in] ptr The initial pointer to be freed.
 * @param[in] ... Additional pointers to be freed (variadic arguments).
 *
 * @return void.
 */
void leave_game(void *ptr, ...);
void leave_game(void *ptr, ...);

#endif  // !PRIVATE_GAME_MODULE_H
