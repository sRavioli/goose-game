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

/**
 *  @def MIN_DICE_THROW
 *  @brief The minimum allowed number that a dice throw can assume.
 */
#define MIN_DICE_THROW 1

/**
 *  @def MAX_DICE_THROW
 *  @brief The maximum allowed number that a dice throw can assume.
 */
#define MAX_DICE_THROW 6

/**
 *  @def LINE_END
 *  @brief The character that defines a line termination.
 */
#define LINE_END "\n"

/**
 *  @def STR_END
 *  @brief The character that defines the end of a string.
 */
#define STR_END '\0'

/**
 *  @def STR_EMPTY
 *  @brief The character that defines an empty string.
 */
#define STR_EMPTY ""

/**
 *  @def SPACE_CHAR
 *  @brief The default value that a space assumes.
 */
#define SPACE_CHAR ' '

// boolean replacement (for visual clarity)

/**
 * @def FALSE
 * @brief The default value for a boolean false. (used for visual clarity)
 */
#define FALSE 0

/**
 * @def TRUE
 * @brief The default value for a boolean true. (used for visual clarity)
 */
#define TRUE (!FALSE)

#endif  // GLOBALS_H
