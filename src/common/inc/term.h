// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file term.h
 * @brief Header file containing utility functions for terminal manipulation.
 *
 * This file defines various utility functions for terminal manipulation,
 * such as clearing the screen, retrieving the terminal size, printing menus,
 * and checking key inputs.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-05-17 09:30
 * @version 2.0
 * @copyright GNU GPLv3
 */
#ifndef TERMINAL_UTILS_H
#define TERMINAL_UTILS_H

#include <stdio.h>

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @defgroup KeyboardKeys Keyboard Keys
 * @{
 */

/**
 * @brief The ASCII value that represents the ESC key.
 */
#define ESC 27

/**
 * @brief The ASCII value that represents the ENTER key.
 */
#define ENTER 13

/**
 * @brief The ASCII value that represents the SPACEBAR key.
 */
#define SPACEBAR 32
/** @} */  // End of KeyboardKeys group

// ------------------------------------------------------------

/**
 * @brief The title to display in each screen.
 */
#define TITLE_BAR "IL GIOCO DELL'OCA\n"

/**
 * @brief The maximum number of lines a menu can have.
 */
#define MAX_MENU_LINES 10

/**
 * @brief The maximum number of lines a file that will be printed can have
 */
#define MAX_FILE_LINES 23

// ------------------------------------------------------------

/**
 * @defgroup TextColors Text Colors
 * @{
 */

/**
 * @brief Black text color.
 */
#define BLACK "\x1B[30m"

/**
 * @brief Red text color.
 */
#define RED "\x1B[31m"

/**
 * @brief Green text color.
 */
#define GREEN "\x1B[32m"

/**
 * @brief Yellow text color.
 */
#define YELLOW "\x1B[33m"

/**
 * @brief Blue text color.
 */
#define BLUE "\x1B[34m"

/**
 * @brief Magenta text color.
 */
#define MAGENTA "\x1B[35m"

/**
 * @brief Cyan text color.
 */
#define CYAN "\x1B[36m"

/**
 * @brief White text color.
 */
#define WHITE "\x1B[37m"

/**
 * @brief Reset text color to default.
 */
#define RESET "\x1B[0m"
/** @} */  // End of TextColors group

// ------------------------------------------------------------

/**
 * @defgroup BackgroundColors Background Colors
 * @{
 */

/**
 * @brief Black background color.
 */
#define BG_BLACK "\x1B[40m"

/**
 * @brief Red background color.
 */
#define BG_RED "\x1B[41m"

/**
 * @brief Green background color.
 */
#define BG_GREEN "\x1B[42m"

/**
 * @brief Yellow background color.
 */
#define BG_YELLOW "\x1B[43m"

/**
 * @brief Blue background color.
 */
#define BG_BLUE "\x1B[44m"

/**
 * @brief Magenta background color.
 */
#define BG_MAGENTA "\x1B[45m"

/**
 * @brief Cyan background color.
 */
#define BG_CYAN "\x1B[46m"

/**
 * @brief White background color.
 */
#define BG_WHITE "\x1B[47m"
/** @} */  // End of BackgroundColors group

// ------------------------------------------------------------

/**
 * @defgroup TextStyles Text Styles
 * @{
 */

/**
 * @brief Bold text style.
 */
#define BOLD "\x1B[1m"

/**
 * @brief Underline text style.
 */
#define UNDERLINE "\x1B[4m"

/**
 * @brief Inverse text style.
 */
#define INVERSE "\x1B[7m"
/** @} */  // End of TextStyles group

// ------------------------------------------------------------

/**
 * @brief Reset text formatting to default.
 */
#define RESET "\x1B[0m"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Retrieve the terminal size (width and height).
 *
 * This function retrieves the terminal size (width and height)  and stores
 * the retrieved values in the provided pointers.
 *
 * @param[in,out] width  Pointer to an integer that will hold the width of the
 *                        terminal window.
 * @param[in,out] height Pointer to an integer that will hold the height of the
 *                       terminal window.
 *
 * @return void.
 */
void get_term_size(int *width, int *height);

/**
 * @brief Clears the terminal screen.
 *
 * This function clears the terminal screen using the Windows API.
 *
 *  @return void.
 */
void clear_screen();

/**
 * @brief Clears the current line in the console output.
 *
 * This function clears the content of the current line in the console output.
 * It moves the cursor to the beginning of the line and fills the line with
 * empty spaces.
 *
 * @note This function uses Windows API for console manipulation.
 *
 * @return void.
 */
void clear_line();

/**
 * @brief Creates a new screen for displaying content.
 *
 * This function clears the screen, prints a title bar at the top center of the
 * screen, and draws a horizontal line below the title bar. The title bar is
 * centered based on the terminal width.
 *
 * @note This function relies on the following helper functions:
 *       - @c clear_screen(): Clears the entire console screen.
 *       - @c get_term_size(int* width, int* height): Retrieves the size of the
 *         terminal.
 *
 * @return void.
 */
void new_screen();

/**
 * @brief Prints a menu from a file on the console screen.
 *
 * This function reads a menu file and prints its contents on the console
 * screen. It calculates the necessary padding to center the menu horizontally
 * and vertically based on the terminal size. The menu entries are printed with
 * left padding to center them horizontally.
 *
 * @param[in] filename The path to the menu file to be printed.
 *
 * @note This function relies on the following helper functions:
 *       - @c get_term_size(int* width, int* height): Retrieves the size of the
 *         terminal.
 * @note The file path @b must be relative to the ./src/ folder (or absolute).
 *
 * @return void.
 */
void print_menu(const char filename[]);

/**
 * @brief Prints the contents of a file on the console screen.
 *
 * This function reads a file and prints its contents on the console screen.
 * It reads the file line by line and prints each line until the end of the file
 * or until the maximum number of lines is reached.
 *
 * @param[in] filename The path to the file to be printed.
 *
 * @note The file path @b must be relative to the ./src/ folder (or absolute).
 *
 * @return void
 */
void print_file(const char filename[]);

/**
 * @brief Displays the contents of a file on the console.
 *
 * This function reads and prints the contents of the file with the specified
 * filename to the standard output (stdout). After displaying the file, it waits
 * for a back key to be pressed (b/ESC/ENTER/SPACEBAR) to exit the view.
 *
 * @param[in] filename The name of the file to display.
 *
 * @return void.
 */
void display_file(const char filename[]);

/**
 * @brief Checks if a key is a "back" key.
 *
 * This function determines whether a given key character represents a "back"
 * action, typically used to navigate back or exit from a menu or view.
 *
 * @param[in] key The key character to be checked.
 *
 * @return @c TRUE if the key is a "back" key, @c FALSE otherwise.
 */
int is_back_key(const char key);

/**
 * @brief Checks if a key is a "quit" key.
 *
 * This function determines whether a given key character represents a "quit"
 * action, typically used to exit or quit a program or application.
 *
 * @param[in] key The key character to be checked.
 *
 * @return @c TRUE if the key is a "quit" key, @c FALSE otherwise.
 */
int is_quit_key(const char key);

/**
 * @brief Waits for a keypress and displays a formatted message.
 *
 * This function waits for a keypress from the user and displays a formatted
 * message on the console using the provided format string and optional
 * arguments. The format string follows the same syntax as the printf function.
 * After displaying the message, it waits for a keypress to continue.
 *
 * @param[in] format The format string for the message.
 * @param[in] ...    Optional arguments for the format string.
 *
 * @return void.
 */
void wait_keypress(const char format[], ...);

/**
 * @brief Checks if the given file is empty.
 *
 * This function checks if the specified file is empty by moving the file
 * pointer to the end of the file using fseek and checking the file position
 * using ftell. If the file is empty, it returns TRUE; otherwise, it returns
 * FALSE.
 *
 * @param[in] fp The file pointer of the file to check.
 *
 * @return TRUE if the file is empty, FALSE otherwise.
 */
int is_file_empty(FILE *fp);

#endif  // !TERMINAL_UTILS_H
