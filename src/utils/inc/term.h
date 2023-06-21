// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef TERMINAL_UTILS_H
#define TERMINAL_UTILS_H

/**
 * @brief Retrieve the terminal size.
 *
 * This function retrieves the width and height of the terminal and stores them
 * in the provided integer pointers `width` and `height`, respectively. The
 * terminal size represents the number of columns (width) and rows (height) in
 * the terminal.
 *
 * @param[out] width  A pointer to an integer variable to store the terminal
 *                    width.
 * @param[out] height A pointer to an integer variable to store the terminal
 *                    height.
 *
 * @note The function retrieves the terminal size using platform-specific
 *       methods. On Windows systems, it uses the Windows API. On other systems,
 *       it uses ioctl.
 * @warning The function assumes that the provided `width` and `height` pointers
 *          are valid and can be written to. It does not perform null pointer
 *          checks.
 */
void get_term_size(int *width, int *height);

/**
 * @brief Clear the terminal screen.
 *
 * This function clears the entire terminal screen, effectively removing all
 * content currently displayed. The behavior depends on the underlying platform.
 * On Windows systems, it uses the Windows API functions to clear the screen. On
 * other systems, it relies on ANSI escape sequences to achieve the same effect.
 *
 * @note The function uses platform-specific methods to clear the screen.
 *       On Windows systems, it uses the Windows API. On other systems, it uses
 *       ANSI escape sequences.
 */
void clear_screen();

/**
 * @brief Clear the current line in the terminal.
 *
 * This function clears the content of the current line in the terminal,
 * effectively removing all characters displayed on that line. The behavior
 * depends on the underlying platform. On Windows systems, it uses the Windows
 * API functions to clear the line. On other systems, it relies on ANSI escape
 * sequences to achieve the same effect.
 *
 * @note The function uses platform-specific methods to clear the line.
 *       On Windows systems, it uses the Windows API. On other systems, it uses
 *       ANSI escape sequences.
 */
void clear_line();

#endif  // !TERMINAL_UTILS_H
