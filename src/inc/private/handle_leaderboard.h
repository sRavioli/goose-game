#ifndef LEADERBOARD_MODULE_PRIVATE_H
#define LEADERBOARD_MODULE_PRIVATE_H

#include "../../types/entries.h"

/**
 * @brief Swaps two entries.
 *
 * This function swaps the positions of two entries.
 *
 * @param[in,out] ei A pointer to the first Entry to swap.
 * @param[in,out] ej A pointer to the second Entry to swap.
 *
 * @return void.
 */
void swap_entries(Entry *ei, Entry *ej);

/**
 * @brief Removes duplicate entries.
 *
 * This function removes entries with the same name from the Entries array.
 *
 * @param[in,out] es A pointer to the Entries struct to remove duplicates from.
 *
 * @return void.
 */
void rm_duplicate_entries(Entries *es);

#endif  // !LEADERBOARD_MODULE_PRIVATE_H
