// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file math.h
 * @brief Header file for maths related functions.
 *
 * This file contains declarations for functions related to mathematical
 * operations such as a proportion or rolling two die.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-05-17 09:31
 * @version 1.5
 * @copyright GNU GPLv3
 */
#ifndef MATHS_UTILS_H
#define MATHS_UTILS_H

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @}
 * @defgroup DiceConstants Dice Constants
 * @brief Constants related to dice throwing.
 * @{
 */

/**
 * @brief Minimum value of a dice throw.
 */
#define MIN_DICE_THROW 1

/**
 * @brief Maximum value of a dice throw.
 */
#define MAX_DICE_THROW 6
/** @} */  // End of DiceConstants group

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Calculates the proportion given a numerator, known value, and
 *        denominator.
 *
 * This function calculates the proportion by multiplying the numerator with the
 * known value and then dividing it by the denominator. The result is returned
 * as an integer.
 *
 * @param[in] numerator   The numerator value.
 * @param[in] known_value The known value.
 * @param[in] denominator The denominator value.
 *
 * @return The calculated proportion as an integer.
 */
int proportion(const int numerator, const int known_value,
               const int denominator);

/**
 * @brief Rolls two dice and returns the sum of their values.
 *
 * This function simulates rolling two dice by generating random numbers using
 * the rand() function. It returns the sum of the values obtained from rolling
 * the dice.
 *
 * @return The sum of the values obtained by rolling two dice.
 */
int roll_dice();

/**
 * @brief Swaps the values of two integers.
 *
 * This function swaps the values of two integers by using a temporary variable.
 * The value pointed to by @e n is stored in @e temp, the value pointed to by
 * @e m is assigned to @e n, and the value stored in @e temp is assigned to
 * @e m. After the swap, the original values of @e n and @e m are interchanged.
 *
 * @param[in,out] n A pointer to the first integer.
 * @param[in,out] m A pointer to the second integer.
 *
 * @return void.
 */
void swap_int(int *n, int *m);

#endif  // !MATHS_UTILS_H
