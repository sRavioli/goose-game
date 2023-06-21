// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef LEADERBOARD_MODULE_H
#define LEADERBOARD_MODULE_H

#include "../common/inc/logger.h"
#include "../common/inc/string.h"
#include "../common/inc/term.h"

#include "../types/entries.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

/**
 * @brief Appends entries to an existing array.
 *
 * This function appends new entries to an existing @c Entries array.
 *
 * @param[in,out] existing_entries A pointer to the existing @c Entries struct
 *                                 to append to.
 * @param[in]     new_entries      A pointer to the @c Entries struct containing
 *                                 the new entries to append.
 *
 * @return void.
 */
void append_entries(Entries *existing_entries, Entries *new_entries);

#endif  // !LEADERBOARD_MODULE_H
