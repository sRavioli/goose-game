// Copyright (c) 2023 @authors. GNU GPLv3.

#ifndef ERROR_FORMATS_H
#define ERROR_FORMATS_H

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

#define THROW_ERROR_FORMAT "%s[%s()]%s error: %s.%s\n"

#define STR_ALLOCATION_FAILED_ERROR                                            \
  "failed to allocate memory for string of size '%i'"

#define INVALID_FILENAME_ERROR "given file name (%s) is invalid\n"
#define FILE_NOT_WRITABLE_ERROR "failed to write to file '%s'"
#define FILE_NOT_READABLE_ERROR "failed to read from file '%s'"

#define VALUE_OUT_OF_BOUNDS_ERROR                                              \
  "value of %s is out of bounds, please retry.\n"
#define INVALID_INPUT_ERROR "invalid input, please enter a valid input\n"

#define DUPLICATE_USERNAME_ERROR "this is %s username! please change yours.\n"
#define INVALID_USERNAME_ERROR "this (%s) username is invalid, please retry.\n"

#define ALLOCATION_FAILED_ERROR                                                \
  "failed to allocate memory for pointer with size '%i'\n"

#define INVALID_KEY_ERROR "key '%c' does nothing."

/**
 * @brief The error message for call stack overflow.
 *
 * The @c CALL_STACK_OVERFLOW_ERROR macro represents the error message that is
 * displayed when trying to push a call onto the call stack beyond its maximum
 * allowed depth. It includes placeholders for the index where the call is
 * attempted to be pushed and the maximum allowed index.
 */
#define CALL_STACK_OVERFLOW_ERROR                                              \
  "call stack overflow! trying to push call at index %i, while max is %i\n"

/**
 * @brief The error message for call stack underflow.
 *
 * The @c CALL_STACK_UNDERFLOW_ERROR macro represents the error message that is
 * displayed when trying to pop a call from an empty call stack. It indicates
 * that the call stack is empty and no calls can be popped.
 */
#define CALL_STACK_UNDERFLOW_ERROR                                             \
  "call stack underflow! trying to pop call but the call stack is empty.\n"

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Throws an error and terminates the program.
 *
 * This function throws an error by formatting the error message using a
 * variadic argument list and printing it to the standard error stream (stderr).
 * The error message is constructed based on the given format string and
 * additional arguments. The caller's name is also included in the error
 * message. After printing the error message, the program is terminated with a
 * failure exit status.
 *
 * @param[in] caller  The name of the function or caller throwing the error.
 * @param[in] format  The format string for the error message.
 * @param[in] va_list Additional arguments to be formatted into the error
 *                    message.
 *
 * @note The function should be used as follows:
 *       @code{.c}
 *       throw_err(__func__, <formatted-error-message>, <other-arguments>, ...);
 *       @endcode
 *
 * @return This function does not return as the program is terminated.
 */
void throw_err(const char caller[], const char format[], ...);

/**
 * @brief Prints an error message to the standard error stream.
 *
 * This function formats the error message using a variadic argument list and
 * prints it to the standard error stream (stderr). The error message is
 * constructed based on the given format string and additional arguments.
 *
 * @param[in] format  The format string for the error message.
 * @param[in] va_list Additional arguments to be formatted into the error
 *                    message.
 *
 * @note The function should be used as follows:
 *       @code{.c}
 *       print_err(<formatted-error-message>, <other-arguments>, ...);
 *       @endcode
 *
 * @return void.
 */
void print_err(const char format[], ...);

#endif  // !ERROR_FORMATS_H
