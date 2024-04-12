// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef ENTRIES_TYPE_H
#define ENTRIES_TYPE_H

#include "../types/entry.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief The maximum number of entries allowed on the leaderboard.
 */
#define MAX_ENTRIES 10

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief A struct representing a collection of entries.
 *
 * This struct contains an array of @c Entry structs called @c entries and an
 * integer called @c num_entries which represents the number of entries in the
 * array.
 *
 * @var Entry Entries::entries
 * An array of @c Entry structs.
 *
 * @var int Entries::num_entries
 * The number of entries in the array.
 */
typedef struct Entries {
  Entry entries[MAX_ENTRIES];  ///< An array of @c Entry structs.
  int num_entries;             ///< The number of entries in the array.
} Entries;

/**
 * @brief Gets the number of entries in the Entries struct.
 *
 * This function returns the number of entries currently stored in the
 * @c Entries struct.
 *
 * @param[in] es A pointer to the @c Entries struct.
 *
 * @return The number of entries.
 */
const int get_num_entries(const Entries *es);

/**
 * @brief Sets the number of entries in the Entries struct.
 *
 * This function sets the number of entries currently stored in the @c Entries
 * struct.
 *
 * @param[in,out] es          A pointer to the @c Entries struct.
 * @param[in]     num_entries The new number of entries.
 *
 * @return void.
 */
void set_num_entries(Entries *es, const int num_entries);

/**
 * @brief Gets a pointer to the entries in the Entries struct.
 *
 * This function returns a pointer to the entries array in the @c Entries
 * struct.
 *
 * @param[in,out] es A pointer to the @c Entries struct.
 *
 * @return A pointer to the entries array.
 */
Entry *get_entries(Entries *es);

/**
 * @brief Gets a pointer to a specific entry in the Entries struct.
 *
 * This function returns a pointer to the @c Entry at the specified position
 * in the @c Entries struct.
 *
 * @param[in] es       A pointer to the @c Entries struct.
 * @param[in] position The position of the desired @c Entry.
 *
 * @return A pointer to the desired @c Entry.
 */
Entry get_entry(Entries *es, const int position);

/**
 * @brief Sets an entry in the Entries struct.
 *
 * This function sets the @c Entry at the specified position in the
 * @c Entries struct to the given @c Entry.
 *
 * @param[in,out] es       A pointer to the @c Entries struct.
 * @param[in]     e        A pointer to the new @c Entry.
 * @param[in]     position The position of the @c Entry to be set.
 *
 * @return void.
 */
void set_entry(Entries *es, Entry *e, const int position);

#endif  // !ENTRIES_TYPE_H
