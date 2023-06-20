/**
 * @file leaderboard.c
 * @brief A program to manage a leaderboard of players.
 *
 * This program allows the user to create, read, update and delete entries in a
 * leaderboard of players. Each entry consists of a player username (up to 3
 * characters), and a score. The program can store up to 10 entries. The program
 * reads and writes entries from/to a file named "leaderboard.txt".
 *
 * @note This program uses the scanf_s function to read input, which is a
 *       Microsoft-specific function. If you're using a different compiler, you
 *       might need to use a different function to read input.
 * @note This program uses the strncpy_s function to truncate strings, which is
 *       a Microsoft-specific function. If you're using a different compiler,
 *       you might need to use a different function to truncate strings.
 *
 * @author Simone Fidanza
 * @date April 2023
 * @licence GNU GPLv3
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_END '\0'
#define LINE_END "\n"

#define MAX_NAME_LENGTH 20
#define MAX_USERNAME_LENGTH 3
#define MAX_LINE_LENGTH 20

#define MAX_NUM_PLAYERS 4

#define MAX_ENTRIES 10
typedef struct Entry {
  char username[MAX_USERNAME_LENGTH + 1];
  int score;
} Entry;

void get_name(char *username);
int is_name_valid(const char *username);
void truncate_string(char username[], int length);
void make_uppercase(char username[]);

Entry *create_entry(Entry entries[]);
void store_entries(Entry entries[], int num_entries);

void sort_entries(Entry entries[], int num_entries);
void swap_entries(Entry *entry1, Entry *entry2);

int read_entries(Entry entries[], const char *filename);
void parse_entry(const char *str, Entry *entry);

void write_entries(Entry entries[], int num_entries, const char *filename);
int append_entries(Entry *existing_entries, int existing_num_entries,
                   Entry *new_entries, int new_num_entries);
void remove_duplicates(Entry entries[], int num_entries);

void print_leaderboard(Entry entries[], int num_entries);

typedef struct Entries {
  Entry entries[MAX_ENTRIES];
  int num_entries;
} Entries;

int main(void) {
  Entries entries = {{
                         {"SAR", 990},
                         {"SRV", 990},
                         {"STE", 800},
                         {"ALF", 700},
                         {"DAN", 600},
                         {"SIL", 500},
                         {"ROS", 400},
                         {"ERC", 300},
                         {"TTT", 260},
                         {"QQQ", 240},
                     },
                     10};
  FILE *fp = fopen("leaderboard.bin", "wb");
  fwrite(&entries, sizeof(Entries), 1, fp);
  fclose(fp);
  return EXIT_SUCCESS;
}

/**
 * @brief Gets a valid username from the user, truncates it necessary, and
 *        converts it to uppercase.
 *
 * This function prompts the user to enter a username using printf and reads it
 * using scanf_s. It then checks if the username is valid using is_name_valid.
 * If the username is invalid, it prints an error message and prompts the user
 * to try again. If the username is valid, it truncates it if necessary using
 * truncate_string and converts it to uppercase using make_uppercase.
 *
 * @param username The character array to store the username. It's as long as
 * the maximum allowed username length.
 *
 * @see is_name_valid()
 * @see truncate_string()
 * @see make_uppercase()
 */
void get_name(char username[]) {
  // HACK: this clears the current line. there has to be a better way.
  // printf("\033[A\33[2K\r");
  int valid = 0;
  while (!valid) {
    printf("Enter your username: ");
    scanf_s("%20s", username, MAX_NAME_LENGTH);

    if (is_name_valid(username)) {
      valid = 1;
      truncate_string(username, MAX_USERNAME_LENGTH);
      make_uppercase(username);
    } else {
      printf("Invalid username. Please try again.\n");
    }
  }
}

/**
 * @brief Determines whether a username is valid, i.e. it contains only letters
 *        and spaces.
 *
 * This function checks if the given username is valid. A username is considered
 * valid if it contains only letters and spaces (no digits or punctuation
 * marks). The function returns 1 if the username is valid, and 0 otherwise.
 *
 * @param username The username to validate.
 * @return 1 if the username is valid, 0 otherwise.
 *
 * @see get_name()
 */
int is_name_valid(const char username[]) {
  // handle NULL values
  if (username == NULL) {
    printf("Error while checking string: the string is NULL\n");
    return 0;
  }
  int i = 0;
  while (username[i]) {
    // no need to check for spaces since scanf_s stops at the first whitespace
    // character
    if (ispunct(username[i]) || isdigit(username[i])) {
      return 0;
    }
    i = i + 1;
  }
  return 1;
}

/**
 * @brief Truncates a username to the maximum length allowed.
 *
 * This function truncates a given username to the maximum length allowed
 * (MAX_USERNAME_LENGTH). If the username is already shorter than the maximum
 * length, it does nothing.
 *
 * @param username The username to truncate. Should be as long as the maximum
 *             allowed length + 1.
 *
 * @see get_name()
 */
void truncate_string(char username[], int length) {
  // handle NULL
  if (username == NULL) {
    printf("Error while truncating string: the string is NULL\n");
    return;
  }
  if (strlen(username) > MAX_USERNAME_LENGTH) {
    strncpy_s(username, MAX_NAME_LENGTH, username, length);
  }
}

/**
 * @brief Converts a string to uppercase.
 *
 * This function converts a given string to uppercase using the toupper()
 * function from <ctype.h>. If the username is already in uppercase, it does
 * nothing.
 *
 * @param username The string to convert to uppercase.
 *
 * @see get_name
 */
void make_uppercase(char username[]) {
  if (username == NULL) {
    return;
  }
  int i = 0;
  while (i < strlen(username)) {
    username[i] = toupper(username[i]);
    i = i + 1;
  }
}

/**
 * @brief Creates a new Entry struct and prompts the user to enter their
 * username and score.
 *
 * This function prompts the user to enter their username and score, validates
 * the input, and returns a new dynamically allocated Entry struct containing
 * the input values.
 *
 * @param entries An array of Entry structs that will be populated with the new
 *                entry.
 *
 * @return A pointer to the newly created Entry struct. If an error occurs
 *         during memory allocation, returns NULL.
 *
 * @see store_entries()
 */
Entry *create_entry(Entry entries[]) {
  Entry *new_entry = malloc(sizeof(Entry));
  if (new_entry == NULL) {
    printf("Error: unable to allocate memory for new entry\n");
    return NULL;
  }
  int valid = 0;
  while (!valid) {
    get_name(new_entry->username);
    // TODO: (NOLINT) the score should be calculated in some way during the
    // game, this is just temporary since that calculation is not implemented
    // yet
    printf("Enter your score: ");
    scanf_s("%d", &new_entry->score, sizeof(int));

    if (new_entry->score < 0) {
      printf("Error: score must be non-negative\n");
    } else {
      valid = 1;
    }
  }
  return new_entry;
}

/**
 * @brief Prompts the user to enter the username and score for a specified
 * number of players.
 *
 * This function prompts the user to enter the username and score for a
 * specified number of players, validates the input, and populates an array of
 * Entry structs with the input values.
 *
 * @param entries     An array of Entry structs that will be populated with the
 *                    new entries.
 * @param num_players The number of players to create entries for.
 *
 * @see *create_entry()
 */
void store_entries(Entry entries[], int num_entries) {
  Entry entry;
  int i = 0;
  while (i < num_entries) {
    entry = *create_entry(&entry);
    entries[i] = entry;
    i = i + 1;
  }
}

/**
 * @brief Swaps two Entry structs.
 *
 * Given two pointers to Entry structs, this function swaps their contents
 * using a temporary variable.
 *
 * @param entry1 Pointer to the first Entry to swap.
 * @param entry2 Pointer to the second Entry to swap.
 */
void swap_entries(Entry *entry1, Entry *entry2) {
  Entry temp = *entry1;
  *entry1 = *entry2;
  *entry2 = temp;
}

/**
 * @brief Sorts an array of entries based on score and username.
 *
 * The function sorts an array of Entry structs based on the score and username
 * fields in each struct. Entries with higher scores come first, and if two
 * entries have the same score, they are sorted alphabetically by username.
 *
 * @param entries     The array of Entry structs to sort.
 * @param num_entries The number of entries in the array.
 */
void sort_entries(Entry entries[], int num_entries) {
  int i = 0;
  while (i < num_entries) {
    int j = i + 1;
    while (j < num_entries) {
      int is_score_greater = entries[j].score > entries[i].score;
      int is_score_equal = entries[j].score == entries[i].score;
      int is_name_previous =
          strcmp(entries[j].username, entries[i].username) < 0;
      int should_swap_entries =
          is_score_greater || (is_score_equal && is_name_previous);

      if (should_swap_entries) {
        swap_entries(&entries[i], &entries[j]);
      }
      j = j + 1;
    }
    i = i + 1;
  }
}

/**
 * @brief Reads entries from a file.
 *
 * Given an array of `Entry` structs and a filename, reads each line of the
 * file until the end is met. For each line, parses it into an `Entry` struct
 * and stores it in the given array.
 *
 * @param entries  The array to store the entries in.
 * @param filename The username of the file to read from.
 *
 * @return The number of entries read from the file.
 */
int read_entries(Entry entries[], const char *filename) {
  FILE *fp;
  char line[MAX_LINE_LENGTH];

  // Open the file for reading
  if (fopen_s(&fp, filename, "r") != 0) {
    printf("Failed to open file '%s'\n", filename);
    return -1;
  }

  // Read each line of the file until EOF is met
  int num_entries = 0;
  while (fgets(line, sizeof(line), fp)) {
    Entry entry;
    parse_entry(line, &entry);
    entries[num_entries] = entry;
    num_entries = num_entries + 1;
  }

  // Close the file
  fclose(fp);

  return num_entries;
}

/**
 * @brief Parse a string representing a score entry and fill an Entry struct.
 *
 * The input string should be formatted as "[username] [score]", where
 * [username] is a string of up to MAX_NAME_LENGTH characters and [score] is an
 * integer. The function copies the username to the Entry struct's username
 * field, and the score to its score field.
 *
 * If the input string is not in the expected format, or if the username is too
 * long, the function prints an error message and returns without modifying the
 * Entry struct.
 *
 * @param str   The input string to parse.
 * @param entry A pointer to the Entry struct to fill.
 */
void parse_entry(const char *str, Entry *entry) {
  // Find the space character that separates the username and score. if not
  // present throw an error.
  const char *space = strchr(str, ' ');
  if (space == NULL) {
    printf("Invalid input string: '%s'\n", str);
    return;
  }

  // Calculate the length of the username
  int name_len = space - str;

  // Copy the username to the output buffer
  errno_t err =
      strncpy_s(entry->username, sizeof(entry->username), str, name_len);
  if (err != 0) {
    char buf[256];
    strerror_s(buf, sizeof(buf), err);
    printf("Error copying username: %s\n", buf);
    return;
  }
  entry->username[name_len] = STR_END;

  // Parse the score as an integer
  entry->score = atoi(space + 1);
  // diventa fread(&entries, nomefile)
}

/**
 * @brief Write the provided array of entries to a file.
 *
 * This function reads entries from the specified file, appends the provided
 * entries to the array, sorts the entries, removes duplicates, and then writes
 * the entries to the file. If the provided array of entries is NULL or if the
 * filename is empty, an error message will be printed and the function will
 * return without writing to the file.
 *
 * @param entries     The array of entries to write to the file.
 * @param num_entries The number of entries in the array.
 * @param filename    The username of the file to write to.
 */
void write_entries(Entry entries[], int num_entries, const char *filename) {
  // Check if entries is NULL
  if (entries == NULL) {
    printf("Error while writing entries: entries is NULL.\n");
    return;
  }

  // Check if filename is empty
  if (strlen(filename) == 0) {
    printf("Error while opening file: no filename given.\n");
    return;
  }

  // read entries from file and put them in an array. Append entries that need
  // to be written to file to the prev array.
  Entry file_entries[MAX_ENTRIES + MAX_NUM_PLAYERS];
  int num_file_entries = read_entries(file_entries, filename);
  int num_total_entries =
      append_entries(file_entries, num_file_entries, entries, num_entries);

  // sort entries before writing to file. This way the high scores will always
  // be inside the top 10 (MAX_ENTRIES).
  sort_entries(file_entries, num_total_entries);
  remove_duplicates(file_entries, num_total_entries);

  // debug
  // print_leaderboard(file_entries, MAX_ENTRIES);

  FILE *fp;

  // Open the file for writing
  if (fopen_s(&fp, filename, "w") != 0) {
    printf("Failed to open file '%s' for writing\n", filename);
    return;
  }

  // Write each entry to the file
  int i = 0;
  while (i <= MAX_ENTRIES) {
    const Entry *entry = &file_entries[i];
    fprintf(fp, "%s %d\n", entry->username, entry->score);
    i = i + 1;
  }

  // Close the file
  fclose(fp);
}

/**
 * @brief Append the provided array of entries to an existing array.
 *
 * This function copies the provided array of entries to the end of an existing
 * array of entries and returns the total number of entries in the combined
 * array.
 *
 * @param existing_entries     The existing array of entries to append to.
 * @param existing_num_entries The number of entries in the existing array.
 * @param new_entries          The new array of entries to append.
 * @param new_num_entries      The number of entries in the new array.
 * @return The total number of entries in the combined array.
 */
int append_entries(Entry *existing_entries, int existing_num_entries,
                   Entry *new_entries, int new_num_entries) {
  // Copy the new entries to the end of the existing array
  memcpy(existing_entries + existing_num_entries, new_entries,
         new_num_entries * sizeof(Entry));

  // Update the number of entries
  return existing_num_entries + new_num_entries;
}

/**
 * @brief Remove duplicates from an array of entries.
 *
 * This function removes any duplicate entries from the provided array of
 * entries by shifting all subsequent entries back one index. The number of
 * entries in the array is updated accordingly.
 *
 * @param entries     The array of entries to remove duplicates from.
 * @param num_entries The number of entries in the array.
 */
void remove_duplicates(Entry entries[], int num_entries) {
  int i = 0;
  while (i < num_entries - 1) {
    if (strcmp(entries[i].username, entries[i + 1].username) == 0) {
      int j = i + 1;
      while (j < num_entries - 1) {
        entries[j] = entries[j + 1];
        j = j + 1;
      }
      num_entries = num_entries - 1;
      // Continue checking from this index to ensure no other duplicates were
      // missed
      i = i - 1;
    }
    i = i + 1;
  }
}

/**
 * @brief Prints a leaderboard of entries to the console.
 *
 * The function prints a leaderboard to the console with the rank, username, and
 * score of each entry. The entries are sorted by score in descending order, and
 * entries with the same score are assigned the same rank. The leaderboard is
 * printed with a fixed-width format for each column with the following format:
 * "[rank] [username] [score]"
 *
 * @param entries     An array of Entry structs containing the entries to print.
 * @param num_entries The number of entries in the entries array.
 *
 */
void print_leaderboard(Entry entries[], int num_entries) {
  printf("%6s  %-4s  %-5s\n", "RANK", "username", "SCORE");
  int i = 0;
  int rank = 1;
  int prev_score = -1;
  while (i < num_entries) {
    Entry entry = entries[i];
    if (entry.score != prev_score) {
      prev_score = entry.score;
      rank = i + 1;
    }
    printf("%6d  %-4s  %-5d\n", rank, entry.username, entry.score);
    i = i + 1;
  }
}
