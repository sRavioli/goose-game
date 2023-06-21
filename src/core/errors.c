// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/inc/logger.h"
#include "../common/inc/string.h"
#include "../common/inc/term.h"

#include "../inc/errors.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

void throw_err(const char caller[], const char format[], ...) {
  logger.enter_fn(__func__);

  char buffer[MAX_BUFFER_LEN];  // will receive the error message

  // format the error message into the buffer
  logger.log("formatting error message to buffer");
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  // print to stderr the error
  logger.log("printing error to stderr");
  fprintf(stderr, THROW_ERROR_FORMAT, YELLOW, caller, RED, buffer, RESET);

  logger.log("terminating program");
  logger.stop();
  _fcloseall();
  exit(EXIT_FAILURE);  // terminate the program
}

void print_err(const char format[], ...) {
  logger.enter_fn(__func__);

  char buffer[MAX_BUFFER_LEN];  // will receive the error message

  // format the error message into the buffer
  logger.log("formatting error message to buffer");
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  // print to stderr the error
  logger.log("printing error to stderr");
  fprintf(stderr, "%s", buffer);

  logger.exit_fn();
}
