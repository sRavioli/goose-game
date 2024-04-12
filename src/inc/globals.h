// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file globals.h
 *
 * @brief Global constants and definitions for the board game module.
 *
 * This file contains some global default values used in the project.
 *
 * @warning This file should be included in any source file that needs to
 *          access these global constants and definitions.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-07-08 12:40
 * @version 1.5
 * @copyright GNU GPLv3
 */

#ifndef GLOBALS_H
#define GLOBALS_H

// GLOBAL CONSTANTS LIST

// boolean replacement (for visual clarity)
// Instead of having 1/0 used as booleans, make them macros. This makes the code
// more clear.

/**
 * @brief The default value for a boolean false. (used for visual clarity)
 */
#define FALSE 0

/**
 * @brief The default value for a boolean true. (used for visual clarity)
 */
#define TRUE (!FALSE)

/**
 * @brief Return value indicating that an index was not found.
 */
#define INDEX_NOT_FOUND -1

/**
 * @brief Base for decimal numbers.
 */
#define DECIMAL_BASE 10

/**
 * @brief Path to the main menu text file.
 */
#define MAIN_MENU "../res/text/menus/main.txt"

/**
 * @brief Path to the pause menu text file.
 */
#define PAUSE_MENU "../res/text/menus/pause.txt"

/**
 * @brief Path to the help menu text file.
 */
#define HELP_MENU "../res/text/menus/help.txt"

/**
 * @brief Path to the saved menu text file.
 */
#define SAVED_MENU "../res/text/menus/saved.txt"

/**
 * @brief Path to the rules text file.
 */
#define RULES_FILE "../res/text/rules.txt"

/**
 * @brief Path to the manual text file.
 */
#define MANUAL_FILE "../res/text/manual.txt"

/**
 * @brief Path to the saved games binary file.
 */
#define SAVED_GAMES_FILE "../res/data/saves.bin"

/**
 * @brief Path to the leaderboard binary file.
 */
#define LEADERBOARD_FILE "../res/data/leaderboard.bin"

#endif  // GLOBALS_H
