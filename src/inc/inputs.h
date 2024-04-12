// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file inputs.h
 * @brief This file contains various input formats and messages used in the
 * game.
 *
 * The file defines format strings and messages used for displaying prompts,
 * input instructions, and game-related information.
 *
 * The format strings include placeholders for dynamic values such as player
 * names, numbers, and dice rolls. They are used to generate formatted strings
 * at runtime to provide clear instructions and display game information to the
 * players.
 *
 * @note This file does not contain any functions or types. It only defines
 *       format strings and messages.
 */
#ifndef INPUT_FORMATS_H
#define INPUT_FORMATS_H

/**
 * @brief Format string for prompting the user to insert the desired number
 * within a specified range.
 *
 * Use with printf-like functions: `printf(ASK_BOUND_VALUE_FMT, "items", min,
 * max);` The placeholders %s, %d, and %d should be replaced with the
 * appropriate values.
 */
#define ASK_BOUND_VALUE_FMT "Insert the desired number of %s [%d, %d]: "

/**
 * @brief Format string for prompting a specific player to enter their username.
 *
 * Use with printf-like functions: printf(ASK_USERNAME_FMT, playerNumber);
 * The placeholder %i should be replaced with the appropriate player number.
 */
#define ASK_USERNAME_FMT "Player %i, enter your username: "

/**
 * @brief Format string for printing the valid username to the console.
 *
 * Use with printf-like functions: printf(PRINT_VALID_USERNAME_FMT, username);
 * The placeholder %s should be replaced with the appropriate username.
 */
#define PRINT_VALID_USERNAME_FMT "your username will be: %s\n"

/**
 * @brief Title for the username selection screen.
 */
#define USERNAME_SCREEN_TITLE "\nUSERNAME SELECTION\n"

/**
 * @brief Format string for prompting a player to press any key to roll the
 * dice.
 *
 * Use with printf-like functions: printf(PRESS_TO_ROLL_FMT, playerName);
 * The placeholder %s should be replaced with the appropriate player name.
 */
#define PRESS_TO_ROLL_FMT "%s press any key to roll dice"

/**
 * @brief Format string for printing the result of a dice roll.
 *
 * Use with printf-like functions: printf(ROLL_RESULT_FMT, playerName,
 * rollValue); The placeholders %s and %d should be replaced with the
 * appropriate player name and roll value.
 */
#define ROLL_RESULT_FMT "%s rolled a %d\n"

/**
 * @brief Format string for prompting a player to press any key to re-roll the
 * dice.
 *
 * Use with printf-like functions: printf(PRESS_TO_REROLL_FMT, playerName);
 * The placeholder %s should be replaced with the appropriate player name.
 */
#define PRESS_TO_REROLL_FMT "%s press any key to re-roll"

/**
 * @brief Format string for printing the result of a re-roll.
 *
 * Use with printf-like functions: printf(REROLL_RESULT_FMT, playerName,
 * rollValue); The placeholders %s and %d should be replaced with the
 * appropriate player name and roll value.
 */
#define REROLL_RESULT_FMT "%s rerolled and got a %d\n"

/**
 * @brief Message indicating a tie in dice rolls and the need for rerolling.
 */
#define DICE_TIE_MSG "Tie detected! Rerolling for tied players:\n"

/**
 * @brief Message indicating the final order based on the dice rolls.
 */
#define FINAL_ORDER_MSG "Based on the dice rolls, the turn order is:\n"

#define LEADERBOARD_BANNER "RANK USERNAME SCORE\n"

#endif  // !INPUT_FORMATS_H
