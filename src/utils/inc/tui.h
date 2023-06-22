// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef TUI_UTILS_H
#define TUI_UTILS_H

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
#define TITLE_BAR "%sIL GIOCO DELL'OCA%s\n"

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
 * @brief Create a new screen.
 *
 * This function clears the screen, prints a title bar, and a horizontal
 * separator. It calculates the appropriate padding to center the title bar and
 * menu entries. The appearance of the screen depends on the underlying
 * platform.
 *
 * @note The function uses platform-specific methods to clear the screen, print
 *       characters, and retrieve the terminal size.
 */
void new_screen();

/**
 * @brief Print a menu from a file.
 *
 * This function clears the screen, reads the contents of the specified file,
 * and prints the menu entries on the screen. It calculates the appropriate
 * padding to center the menu entries. The number of lines and the maximum line
 * length are limited. The appearance of the menu depends on the underlying
 * platform.
 *
 * @param[in] filename The name of the file containing the menu entries.
 *
 * @note The function uses platform-specific methods to clear the screen, read
 *       the file, print characters, and retrieve the terminal size.
 */
void print_menu(const char filename[]);

/**
 * @brief Print the contents of a file.
 *
 * This function clears the screen and prints the contents of the specified
 * file. The appearance of the file contents depends on the underlying platform.
 *
 * @param[in] filename The name of the file to be printed.
 *
 * @note The function uses platform-specific methods to clear the screen, read
 *       the file, and print characters.
 */
void print_file(const char filename[]);

/**
 * @brief Check if a key represents a back action.
 *
 * This function checks if the provided character `key` corresponds to a key
 * that represents a back action, such as `ESC`, `ENTER`, `SPACEBAR`, or 'b'.
 *
 * @param[in] key The character representing the pressed key.
 *
 * @return `TRUE` (1) if the key is a back action, otherwise `FALSE` (0).
 */
int is_back_key(const char key);

/**
 * @brief Check if a key represents a quit action.
 *
 * This function checks if the provided character `key` corresponds to a key
 * that represents a quit action, such as `ESC` or 'q'.
 *
 * @param[in] key The character representing the pressed key.
 *
 * @return `TRUE` (1) if the key is a quit action, otherwise `FALSE` (0).
 */
int is_quit_key(const char key);

/**
 * @brief Display the contents of a file on the screen.
 *
 * This function prints the contents of the specified file on the screen,
 * clears the screen, and displays a message indicating how to exit the view.
 * The appearance of the file contents and the exit message depends on the
 * underlying platform.
 *
 * @param[in] filename The name of the file to be displayed.
 *
 * @note The function uses platform-specific methods to clear the screen, read
 *       the file, print characters, and wait for a keypress.
 */
void display_file(const char filename[]);

/**
 * @brief Wait for a keypress.
 *
 * This function displays a formatted message and waits for a keypress from the
 * user. While waiting, it displays a spinner animation. The appearance of the
 * spinner animation and the keypress handling depends on the underlying
 * platform.
 *
 * @param[in] format  The format string for the message to be displayed.
 * @param[in] va_list Additional arguments to be formatted according to the
 *                    format string.
 *
 * @note The function uses platform-specific methods to display the message,
 *       wait for a keypress, print characters, and handle the spinner
 *       animation.
 */
void wait_keypress(const char format[], ...);

#endif  // !TUI_UTILS_H
