// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef LEADERBOARD_MODULE_H
#define LEADERBOARD_MODULE_H

#include "../common/inc/types/entries.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

#define NO_ENTRIES 0

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Writes a leaderboard entry to the file.
 *
 * This function writes the provided entry to the leaderboard file. If the
 * leaderboard file is already full (MAX_ENTRIES), it checks if the last entry
 * has a higher score than the provided entry. If it does, the entry is not
 * written. If the leaderboard file has space for additional entries, the entry
 * is appended to the end. If a duplicate entry is found, it is overwritten with
 * the provided entry. After writing, the leaderboard is sorted, and any
 * duplicate entries are removed.
 *
 * @param[in] e The Entry to write to the leaderboard file.
 *
 * @return void.
 */
void write_leaderboard(Entry e);

/**
 * @brief Displays the leaderboard view.
 *
 * This function reads the leaderboard data, displays the leaderboard using
 * display_leaderboard, and waits for a back key (b/ESC/ENTER/SPACEBAR) to be
 * pressed before returning.
 *
 * @return void.
 */
void leaderboard(void);

#endif  // !LEADERBOARD_MODULE_H
