// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef LEADERBOARD_MODULE_PRIVATE_H
#define LEADERBOARD_MODULE_PRIVATE_H

#include "../../common/inc/types/entries.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Reads the leaderboard from a file.
 *
 * This function reads the leaderboard data from a file and populates the
 * provided Entries structure with the leaderboard entries. If the file is
 * empty, the number of entries is set to NO_ENTRIES.
 *
 * @param[in,out] es The Entries structure to populate with the leaderboard
 *                   data.
 *
 * @return void.
 */
void read_leaderboard(Entries *es);

/**
 * @brief Finds a duplicate entry in the leaderboard.
 *
 * This function searches for another entry with the same username in the
 * leaderboard. If a duplicate entry is found, it returns the index of the
 * duplicate entry; otherwise, it returns INDEX_NOT_FOUND.
 *
 * @param[in] es The Entries structure containing the leaderboard entries.
 * @param[in] e  The Entry to search for duplicates of.
 *
 * @return The index of the duplicate entry, or INDEX_NOT_FOUND if no duplicate
 *         is found.
 */
int find_duplicate_entry(Entries es, Entry e);

/**
 * @brief Swaps two leaderboard entries.
 *
 * This function swaps the positions of two leaderboard entries.
 *
 * @param[in,out] first  Pointer to the first Entry to swap.
 * @param[in,out] second Pointer to the second Entry to swap.
 *
 * @return void.
 */
void swap_entries(Entry *first, Entry *second);

/**
 * @brief Removes duplicate entries from the leaderboard.
 *
 * This function removes duplicate entries from the leaderboard by shifting the
 * subsequent entries to fill the gaps. It ensures that only unique entries
 * remain in the leaderboard.
 *
 * @param[in,out] es The Entries structure containing the leaderboard entries.
 *
 * @return void.
 */
void rm_duplicate_entries(Entries *es);

/**
 * @brief Sorts the leaderboard entries.
 *
 * This function sorts the leaderboard entries based on the final score and
 * username. Entries with higher scores come first, and in case of ties, entries
 * with lexicographically smaller usernames come first. After sorting, any
 * duplicate entries are removed from the leaderboard.
 *
 * @param[in,out] es The Entries structure containing the leaderboard entries.
 *
 * @return void.
 */
void sort_entries(Entries *es);

/**
 * @brief Prints the leaderboard to the console.
 *
 * This function prints the leaderboard entries to the console. It displays the
 * rank, username, and final score for each entry. Entries are printed in
 * descending order based on the final score, and ties are broken by
 * lexicographically sorting the usernames. If the leaderboard is empty, it
 * prints an appropriate error message.
 *
 * @param[in] es The Entries structure containing the leaderboard entries.
 *
 * @return void.
 */
void print_leaderboard(Entries es);

/**
 * @brief Displays the leaderboard on the console.
 *
 * This function displays the leaderboard on the console by calling
 * print_leaderboard and adding additional formatting. It also waits for a back
 * key (b/ESC/ENTER/SPACEBAR) to be pressed before returning.
 *
 * @param[in] es The Entries structure containing the leaderboard entries.
 *
 * @return void.
 */
void display_leaderboard(Entries es);

#endif  // !LEADERBOARD_MODULE_PRIVATE_H
