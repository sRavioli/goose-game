// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef ENTRY_TYPE_H
#define ENTRY_TYPE_H

#include "./player.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

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
 * @param[in]     name The string containing the name to set.
 *
 * @return void.
 */
void set_name(Entry *e, const char name[]);

/**
 * @brief Gets the score of an Entry.
 *
 * This function returns the score of the specified @c Entry.
 *
 * @param[in] e A pointer to the @c Entry whose score will be returned.
 *
 * @return The score of the specified @c Entry.
 */
const int get_final_score(const Entry *e);

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
void set_final_score(Entry *e, const int final_score);

#endif  // !ENTRY_TYPE_H
