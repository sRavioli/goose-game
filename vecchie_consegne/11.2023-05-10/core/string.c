// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "./string.h"

void concat(char *buffer, const char *source) {
  snprintf(buffer + strlen(buffer), strlen(source) + 1, "%s", source);
}

void nconcat(char *buffer, const char *source, const int n_times) {
  int buffer_length = strlen(buffer);
  int source_len = strlen(source);
  int i = 0;
  while (i < n_times) {
    snprintf(buffer + buffer_length, source_len + 1, "%s", source);
    buffer_length = buffer_length + source_len;
    i = i + 1;
  }
}

void fconcat(char *buffer, const int source_size, const char *format, ...) {
  va_list args;
  va_start(args, format);
  vsnprintf(buffer + strlen(buffer), source_size, format, args);
  va_end(args);
}

char *alloc_char(const char *s, const int size) {
  char *buffer = (char *)malloc(1 + size * strlen(s) * sizeof(s));  // NOLINT
  if (buffer == NULL) {
    printf("error: failed to allocate memory for string of size %i\n", size);
    exit(EXIT_FAILURE);
  }
  // ensure null termination of the string
  memset(buffer, STR_END, strlen(buffer));

  return buffer;
}

void str_copy(char *buffer, const char *source) {
  snprintf(buffer, strlen(source) + 1, "%s", source);
}

void str_truncate(char *buffer, const int len) {
  strncpy_s(buffer, sizeof(buffer), buffer, len);
}

void str_to_uppercase(char *buffer) {
  int buffer_len = strlen(buffer);
  int i = 0;
  while (i < buffer_len) {
    buffer[i] = toupper(buffer[i]);
    i = i + 1;
  }
}
