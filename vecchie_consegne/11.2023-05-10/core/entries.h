#ifndef ENTRIES_TYPE_H
#define ENTRIES_TYPE_H

#include "./globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @def MAX_ENTRIES
 * @brief The maximum number of entries allowed on the leaderboard.
 */
#define MAX_ENTRIES 10

#define MAX_USERNAME_LENGTH 10

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * @brief Defines a struct for a score entry.
 *
 * This struct contains the information needed to define a score entry, such as
 * the name of the player and their score.
 *
 * @var Entry::name
 * The name of the player associated with the score entry.
 *
 * @var Entry::score
 * The score associated with the player.
 */
typedef struct Entry {
  char name[MAX_USERNAME_LENGTH + 1];  ///< The name of the player associated
                                       ///< with the score entry.
  int final_score;  ///< The score associated with the player.
} Entry;

/**
 * @brief Gets the name of an @c Entry.
 *
 * This function returns a pointer to the name of the specified @c Entry.
 *
 * @param[in] e A pointer to the @c Entry whose name will be returned.
 *
 * @return A pointer to the name of the specified @c Entry.
 */
const char *get_name(const Entry *e);

/**
 * @brief Sets the name of an Entry.
 *
 * This function sets the name of the specified @c Entry to the given value.
 * The name is stored as a string, and it will be truncated to a maximum of
 * MAX_USERNAME_LENGTH characters if it is longer than that.
 *
 * @param[in,out] e    A pointer to the @c Entry whose name will be set.
 * @param[in]     name A pointer to the string containing the new name.
 *
 * @return void.
 */
void set_name(Entry *e, const char *name);

/**
 * @brief Gets the score of an Entry.
 *
 * This function returns the score of the specified @c Entry.
 *
 * @param[in] e A pointer to the @c Entry whose score will be returned.
 *
 * @return The score of the specified @c Entry.
 */
int get_final_score(const Entry *e);

/**
 * @brief Sets the score of an Entry.
 *
 * This function sets the score of the specified @c Entry to the given value.
 *
 * @param[in,out] e     A pointer to the @c Entry whose score will be set.
 * @param[in]     score The new score.
 *
 * @return void.
 */
void set_final_score(Entry *e, int final_score);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * @brief A struct representing a collection of entries.
 *
 * This struct contains an array of @c Entry structs called @c entries and an
 * integer called @c num_entries which represents the number of entries in the
 * array.
 *
 * @var Entry *Entries::entries
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
 * @param[in,out] entries A pointer to the @c Entries struct.
 *
 * @return A pointer to the entries array.
 */
Entry *get_entries(Entries *entries);

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
const Entry *get_entry(const Entries *es, const int position);

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

//---------------------------------------

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

#endif  // !ENTRIES_TYPE_H
