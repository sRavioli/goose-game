// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file private/handle_help.h
 * @brief Header file containing the declaration of the help menu handling
 *        functions.
 *
 * This file provides the declaration for the help menu handling functions.
 * It includes the necessary dependencies and defines the required constants.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-05-16 17:33
 * @version 1.0
 * @copyright GNU GPLv3
 */

#ifndef HELP_MODULE_PRIVATE_H
#define HELP_MODULE_PRIVATE_H

/**
 * @brief Prints the help menu.
 *
 * This function clears the screen and prints the contents of the help menu file
 * to the screen using the @c print_menu() function.
 *
 * @return void.
 */
void print_help_menu();

/**
 * @brief Displays the contents of a file on the screen and handles user input.
 *
 * This function clears the screen, prints the contents of the specified file to
 * the screen using the @c print_file() function, and displays an exit message
 * to guide the user on how to exit the view.
 *
 * After displaying the file contents, the function waits for the user to press
 * a key. If the pressed key is a back key (b/ESC/ENTER/SPACEBAR), the function
 * exits and returns to the help menu.
 *
 * @param[in] filename The name of the file to display.
 *
 * @return void.
 */
void display_file(const char filename[]);

#endif  // !HELP_MODULE_PRIVATE_H
