// Copyright (c) 2023 Simone Fidanza – GNU GPLv3
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 3
#define MAX_NAME_LENGTH 20

/**
 * @brief Truncates a username to the maximum length allowed.
 *
 * This function truncates a given username to the maximum length allowed
 * (MAX_USERNAME_LENGTH). If the username is already shorter than the maximum
 * length, it does nothing.
 *
 * @param name The username to truncate. Should be as long as the maximum
 *             allowed length + 1.
 *
 * @see get_name()
 */
void truncate_name(char name[]) {
  if (strlen(name) > MAX_USERNAME_LENGTH) {
    strncpy_s(name, MAX_NAME_LENGTH, name, MAX_USERNAME_LENGTH);
  }
}
void test_truncate_name() {
  char test_name[MAX_USERNAME_LENGTH];

  // Test case 1: Name is shorter than the maximum length
  strncpy(test_name, "test", MAX_USERNAME_LENGTH);
  truncate_name(test_name);
  assert(strcmp(test_name, "tes") == 0);

  // Test case 2: Name is exactly the maximum length
  strncpy(test_name, "a_very_long_name", MAX_USERNAME_LENGTH);
  truncate_name(test_name);
  assert(strcmp(test_name, "a_v") == 0);

  // Test case 3: Name is longer than the maximum length
  strncpy(test_name, "a_really_really_long_name", MAX_USERNAME_LENGTH);
  truncate_name(test_name);
  assert(strcmp(test_name, "a_r") == 0);

  // Test case 4: Name is empty
  strncpy(test_name, "", MAX_USERNAME_LENGTH);
  truncate_name(test_name);
  assert(strcmp(test_name, "") == 0);

  // Test case 5: Name is null
  truncate_name(NULL);  // Function should handle null gracefully
}

int main(void) {
  test_truncate_name();

  return 0;
}
