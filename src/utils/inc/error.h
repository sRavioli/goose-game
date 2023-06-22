// Copyright (c) 2023 @authors. GNU GPLv3.
/**
 * @file error_utils.h
 * @brief This file defines macros and functions related to handling errors.
 *
 * The file contains macro definitions for error messages and a set of functions
 * to print and throw specific errors. It provides a centralized mechanism for
 * managing and reporting errors within a program.
 *
 * The `ERROR_FILE` macro specifies the path to the file containing all the
 * error messages. The file is assumed to have one error message per line.
 *
 * The macro definitions starting from `INVALID_FILENAME_ERROR` to
 * `CALL_STACK_UNDERFLOW_ERROR` assign unique indices to each error message.
 * These indices are used as input to the error handling functions to identify
 * and process specific errors.
 *
 * The `print_err()` function opens the error file, reads the specified error
 * message at the given index, and prints it to the standard output (stdout).
 * It assumes that the file specified by `ERROR_FILE` macro exists and is
 * readable. If the file cannot be opened or read, an error message is printed
 * to the standard output, and the program terminates with a failure status.
 *
 * The `throw_err()` function is similar to `print_err()`, but it also throws
 * the specified error. It opens the error file, reads the error message at the
 * given index, prints it to the standard output, and terminates the program
 * with a failure status. This function is useful for handling critical errors
 * that require immediate termination of the program.
 *
 * @note The functions `print_err()` and `throw_err()` assume that the error
 *       file specified by `ERROR_FILE` macro exists and is readable. If the
 *       file is missing or inaccessible, appropriate error messages are
 *       printed, and the program terminates.
 *
 * @warning It is important to ensure that the error file specified by
 *          `ERROR_FILE` macro is present and accessible. Failure to do so may
 *          result in errors or unexpected program behavior.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-06-21 18:37
 * @version 2.0
 * @copyright GNU-GPLv3
 */
#ifndef ERROR_UTILS_H_
#define ERROR_UTILS_H_

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Path to the file containing all the errors.
 */
#define ERROR_FILE "./res/text/errors.txt"

/**
 * @brief Index of the error message that indicates an invalid filename.
 */
#define INVALID_FILENAME_ERROR 1

/**
 * @brief Index of the error message that indicates that a file is not writable.
 */
#define FILE_NOT_WRITABLE_ERROR 2

/**
 * @brief Index of the error message that indicates that a file is not readable.
 */
#define FILE_NOT_READABLE_ERROR 3

/**
 * @brief Index of the error message that indicates that a value is out of
 * bounds.
 */
#define VALUE_OUT_OF_BOUND_ERROR 4

/**
 * @brief Index of the error message that indicates invalid input.
 */
#define INVALID_INPUT_ERROR 5

/**
 * @brief Index of the error message that indicates a duplicate username.
 */
#define DUPLICATE_USERNAME_ERROR 6

/**
 * @brief Index of the error message that indicates an invalid username.
 */
#define INVALID_USERNAME_ERROR 7

/**
 * @brief Index of the error message that indicates a memory allocation failure.
 */
#define ALLOCATION_ERROR 8

/**
 * @brief Index of the error message that indicates an invalid key.
 */
#define INVALID_KEY_ERROR 9

/**
 * @brief Index of the error message that indicates a call stack overflow.
 */
#define CALL_STACK_OVERFLOW_ERROR 10

/**
 * @brief Index of the error message that indicates a call stack underflow.
 */
#define CALL_STACK_UNDERFLOW_ERROR 11

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Print a specific error from a file.
 *
 * This function attempts to open a file, reads the specified error at the given
 * index, and prints it to the standard output (stdout). The file is assumed to
 * contain errors separated by newline characters ('\n'). The function uses a
 * logger for debugging and error logging purposes.
 *
 * @param[in] index The index of the error to be printed. Indexing starts from
 *                  one.
 *
 * @note The function assumes that the file specified by the `ERROR_FILE` macro
 *       exists and is readable.
 *
 * @warning If the file cannot be opened or read, the function prints an error
 *          message to the standard output and terminates the program with a
 *          failure status.
 *
 * @return void.
 */
void print_err(const int index);

/**
 * @brief Throw and print a specific error from a file.
 *
 * This function attempts to open a file, reads the specified error at the given
 * index, and prints it to the standard output (stdout). The file is assumed to
 * contain errors separated by newline characters ('\n'). The function uses a
 * logger for debugging and error logging purposes.
 *
 * @param[in] index The index of the error to be thrown and printed. Indexing
 *                  starts from one.
 *
 * @note The function assumes that the file specified by the `ERROR_FILE` macro
 *       exists and is readable.
 *
 * @warning If the file cannot be opened or read, the function prints an error
 *          message to the standard output and terminates the program with a
 *          failure status.
 *
 * @return void.
 */
void throw_err(const int index);

#endif  // !ERROR_UTILS_H_
