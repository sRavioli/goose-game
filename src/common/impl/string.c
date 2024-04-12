// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common/inc/error.h"
#include "../../inc/globals.h"

#include "../inc/logger.h"
#include "../inc/term.h"

#include "../inc/string.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

void concat(char *buffer, const char source[]) {
  snprintf(buffer + strlen(buffer), strlen(source) + 1, "%s", source);
}

void nconcat(char *buffer, const char source[], const int n_times) {
  int buffer_length = strlen(buffer);
  int source_len = strlen(source);
  int i = 0;
  while (i < n_times) {
    snprintf(buffer + buffer_length, source_len + 1, "%s", source);
    buffer_length = buffer_length + source_len;
    i = i + 1;
  }
}

void fconcat(char *buffer, const int source_size, const char format[], ...) {
  va_list args;
  va_start(args, format);
  vsnprintf(buffer + strlen(buffer), source_size, format, args);
  va_end(args);
}

char *alloc_char(const char *s, const int size) {
  char *buffer = (char *)malloc(1 + size * strlen(s) * sizeof(s));  // NOLINT
  if (buffer == NULL) {
    throw_err(ALLOCATION_ERROR);
  }
  // ensure null termination of the string
  memset(buffer, STR_END, strlen(buffer));

  return buffer;
}

char *str_allocate(const int size) {
  logger.enter_fn(__func__);
  logger.log("attempting to allocate memory for string of size %i", size);
  char *buffer = (char *)malloc(1 + size * sizeof(char));  // NOLINT
  if (!buffer) {
    logger.exit_fn();
    throw_err(STRING_ALLOCATION_ERROR);
  }
  logger.log("successfully allocated memory for string of size %i", size);

  // ensure null termination of the string
  memset(buffer, STR_END, strlen(buffer));

  logger.exit_fn();
  return buffer;
}

void str_copy(char *buffer, const char source[]) {
  logger.enter_fn(__func__);
  snprintf(buffer, strlen(source) + 1, "%s", source);
  logger.log("copied '%s' to '%s'", source, buffer);
  logger.exit_fn();
}

void str_truncate(char *buffer, const int len) {
  snprintf(buffer, len + 1, "%s", buffer);
}

void str_to_uppercase(char buffer[]) {
  logger.enter_fn(__func__);
  logger.log("uppercasing '%s'", buffer);

  int buffer_len = strlen(buffer);
  int i = 0;
  while (i < buffer_len) {
    buffer[i] = toupper(buffer[i]);
    i = i + 1;
  }
  logger.log("uppercased '%s'", buffer);
}
