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
#include <string.h>
#include <time.h>

#include "../../inc/globals.h"
#include "../inc/error.h"

#include "../inc/string.h"
#include "../inc/term.h"

#include "../inc/logger.h"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief The filename of the log file.
 *
 * The `log_filename` variable stores the filename of the log file. It is a
 * static character array with a maximum length of @c MAX_BUFFER_LEN. This
 * variable is used by the logging functions to specify the log file.
 */
static char log_filename[MAX_BUFFER_LEN];

/**
 * @brief The file pointer to the log file.
 *
 * The `log_fp` variable is a pointer to the log file. It is used to open and
 * close the log file and write log messages into it.
 */
static FILE *log_fp;

/**
 * @brief Indicates whether the logger is active.
 *
 * The `is_logger_active` variable is an integer flag that indicates whether
 * the logger is active or not. A value of @c TRUE indicates that the logger is
 * active and can perform logging operations, while a value of @c FALSE
 * indicates that the logger is inactive and should not perform any logging.
 */
static int is_logger_active = TRUE;

/**
 * @brief Indicates whether the logger has been started.
 *
 * The `is_logger_started` variable is an integer flag that indicates whether
 * the logger has been started. It is set to @c TRUE when the logger is started
 * and the log file is created and can be written to. This flag is used to avoid
 * undesired logging if the logger has not been started.
 */
static int is_logger_started = FALSE;

/**
 * @brief The call stack for logging function calls.
 *
 * The `call_stack` variable is an array of constant character pointers that
 * represents the call stack for logging function calls. It stores the names of
 * functions as strings in the order of their invocation during program
 * execution. The maximum depth of the call stack is defined by the
 * @c MAX_CALLSTACK_DEPTH constant.
 */
static const char *call_stack[MAX_CALLSTACK_DEPTH];

/**
 * @brief The current depth of the call stack.
 *
 * The `current_call_stack_depth` variable is an integer that represents the
 * current depth of the call stack. It indicates the number of function calls
 * that have been logged so far. This value is used to keep track of the
 * position in the call stack and to determine the function to be logged when
 * exiting a function.
 */
static int current_call_stack_depth = 0;

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Pushes a function call onto the call stack.
 *
 * The `push_call` function is used to push the name of a function onto the
 * call stack. It checks if the call stack is already full and throws an error
 * if the maximum depth has been reached. The function call is added to the top
 * of the call stack.
 *
 * @param caller The name of the calling function to be pushed onto the call
 * stack.
 */
void push_call(const char caller[]) {
  // check if the stack is full
  if (current_call_stack_depth > MAX_CALLSTACK_DEPTH) {
    throw_err(CALL_STACK_OVERFLOW_ERROR);
  }

  // Push the calling function onto the call stack
  call_stack[current_call_stack_depth] = caller;
  current_call_stack_depth = current_call_stack_depth + 1;
}

/**
 * @brief Pops a function call from the call stack.
 *
 * The `pop_call` function is used to remove the topmost function call from the
 * call stack. It checks if the call stack is empty and throws an error if an
 * attempt is made to pop a call when the call stack is already empty. The
 * current call stack depth is decremented after the call is removed.
 */
void pop_call() {
  // prevent underflow
  if (current_call_stack_depth <= 0) {
    throw_err(CALL_STACK_UNDERFLOW_ERROR);
  }

  // Pop the topmost function call from the call stack
  current_call_stack_depth = current_call_stack_depth - 1;
}

/**
 * @brief Checks if a filename is valid.
 *
 * The function checks whether a given filename is valid according to certain
 * criteria. It ensures that the filename is not empty, contains only valid
 * characters (alphanumeric, underscore, hyphen, and period), and does not end
 * with a dot or a space.
 *
 * @param[in] filename The filename to be validated.
 *
 * @return Returns an integer value indicating the validity of the filename. It
 *         returns @c TRUE if the filename is valid, and @c FALSE otherwise.
 */
int is_filename_valid(const char filename[]) {
  // check for empty
  if (!filename || !strlen(filename)) {
    return FALSE;
  }

  // check that each char is a valid one
  int i = 0;
  while (i < strlen(filename)) {
    char ch = filename[i];
    if (!isalnum(ch) && ch != '_' && ch != '-' && ch != '.') {
      return FALSE;
    }
    i = i + 1;
  }

  // check if the filename ends with a dot or a space (which is not allowed)
  char last_char = filename[strlen(filename) - 1];
  if (last_char == '.' || last_char == ' ') {
    return FALSE;
  }

  // filename is valid
  return TRUE;
}

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

void start_logger(const char *filename) {
  // check if logging has been disabled
  if (!is_logger_active) {
    return;
  }

  if (!is_filename_valid(filename)) {
    throw_err(INVALID_FILENAME_ERROR);
  }
  // copy given filename to static variable
  snprintf(log_filename, sizeof(log_filename), "%s", filename);

  if (fopen_s(&log_fp, log_filename, "w")) {
    throw_err(FILE_NOT_WRITABLE_ERROR);
  }
  fprintf(log_fp, LOG_BANNER_FMT, LOG_BANNER, LOG_START_MSG, LOG_BANNER);

  // log file has been created and can be written to
  is_logger_started = TRUE;

  fclose(log_fp);
  return;
}

void stop_logger() {
  if (!is_logger_active || !is_logger_started) {  // avoid undesired logging
    return;
  }
  logger.exit_fn();

  // indicate log termination
  if (fopen_s(&log_fp, log_filename, "a")) {
    throw_err(FILE_NOT_WRITABLE_ERROR);
  }
  fprintf(log_fp, LOG_BANNER_FMT, LOG_BANNER, LOG_STOP_MSG, LOG_BANNER);

  // close file
  fclose(log_fp);
  return;
}

void log_event(const char format[], ...) {
  if (!is_logger_active || !is_logger_started) {  // avoid undesired logging
    return;
  }
  // get the current time
  static struct tm timeinfo;
  static char timestamp[20];

  time_t now = time(NULL);
  localtime_s(&timeinfo, &now);
  strftime(timestamp, sizeof(timestamp), TIMESTAMP_FORMAT, &timeinfo);

  // print the formatted message using the variable arguments
  char buffer[MAX_BUFFER_LEN] = "";
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  // create the stack trace for the function that is logging.
  char stack_trace[MAX_BUFFER_LEN] = "";
  int i = 0;
  while (i < current_call_stack_depth) {
    concat(stack_trace, call_stack[i]);
    if (i < current_call_stack_depth - 1) {
      concat(stack_trace, STACK_TRACE_SEPARATOR);
    }
    i = i + 1;
  }

  // safe open
  if (fopen_s(&log_fp, log_filename, "a")) {
    throw_err(FILE_NOT_WRITABLE_ERROR);
  }

  // write to file
  fprintf(log_fp, LOG_MSG_FORMAT, timestamp, stack_trace, buffer);

  // close
  fclose(log_fp);

  return;
}

inline void enter_fn(const char caller[]) { push_call(caller); }
inline void exit_fn() { pop_call(); }

inline void disable_logger() { is_logger_active = FALSE; }
inline void enable_logger() { is_logger_active = TRUE; }

struct Logger logger = {
    .start = start_logger,
    .log = log_event,
    .stop = stop_logger,
    .disable = disable_logger,
    .enable = enable_logger,
    .enter_fn = enter_fn,
    .exit_fn = exit_fn,
};
