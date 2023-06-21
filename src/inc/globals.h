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
 * @date 2023-04-17 13:13
 * @version 1.0
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

#define INDEX_NOT_FOUND -1

#define DECIMAL_BASE 10

#define MAIN_MENU "./res/text/menus/main.txt"
#define PAUSE_MENU "../../res/text/menus/pause.txt"
#define HELP_MENU "../../res/text/menus/help.txt"
#define SAVED_MENU "../../res/text/menus/saved.txt"

#define RULES_FILE "../../res/text/rules.txt"
#define MANUAL_FILE "../../res/text/manual.txt"

#define SAVED_GAMES_FILE "../../res/saves.bin"
#define LEADERBOARD_FILE "../../res/leaderboard.bin"

#endif  // GLOBALS_H
