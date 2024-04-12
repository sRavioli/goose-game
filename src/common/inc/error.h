// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file error.h
 * @brief This file contains error codes and functions for error handling.
 *
 * The file defines error codes that can be used to identify different types of
 * errors. It also includes functions for printing and throwing error messages
 * from an error file.
 *
 * The error codes provide a standardized way to identify and handle errors
 * within the program. The functions allow printing error messages to the
 * standard output and terminating the program with a failure status if
 * necessary.
 *
 * @note This file does not define any types or structures. It only provides
 *       error codes and error handling functions.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-07-11 19:38
 * @version 3.0
 * @copyright GNU GPLv3
 */
#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Path to the error log file.
 */
#define ERROR_FILE "../res/text/errors.txt"

/**
 * @brief Error code indicating an invalid encryption key.
 */
#define INVALID_KEY_ERROR 1

/**
 * @brief Error code indicating a value out of bounds.
 */
#define VALUE_OUT_OF_BOUND_ERROR 2

/**
 * @brief Error code indicating invalid input.
 */
#define INVALID_INPUT_ERROR 3

/**
 * @brief Error code indicating an invalid username.
 */
#define INVALID_USERNAME_ERROR 4

/**
 * @brief Error code indicating a duplicate username.
 */
#define DUPLICATE_USERNAME_ERROR 5

/**
 * @brief Error code indicating a memory allocation failure.
 */
#define ALLOCATION_ERROR 6

/**
 * @brief Error code indicating a string allocation failure.
 */
#define STRING_ALLOCATION_ERROR 7

/**
 * @brief Error code indicating an invalid filename.
 */
#define INVALID_FILENAME_ERROR 8

/**
 * @brief Error code indicating a file is not writable.
 */
#define FILE_NOT_WRITABLE_ERROR 9

/**
 * @brief Error code indicating a file is not readable.
 */
#define FILE_NOT_READABLE_ERROR 10

/**
 * @brief Error code indicating a call stack overflow.
 */
#define CALL_STACK_OVERFLOW_ERROR 11

/**
 * @brief Error code indicating a call stack underflow.
 */
#define CALL_STACK_UNDERFLOW_ERROR 12

/**
 * @brief Error code indicating an invalid game state.
 */
#define INVALID_GAME 13

/**
 * @brief Error code indicating the limit for saves has been reached.
 */
#define LIMIT_SAVES 14

/**
 * @brief Error code indicating no saved games are available.
 */
#define NO_SAVES 15

/**
 * @brief Error code indicating an empty leaderboard.
 */
#define EMPTY_LEADERBOARD 16

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Prints an error message from the error file.
 *
 * This function attempts to open the error file and reads the error message at
 * the specified index. The error message is then printed to the standard output
 * (stdout).
 *
 * @param[in] index The index of the error message to print.
 *
 * @return void.
 */
void print_err(const int index);

/**
 * @brief Prints an error message from the error file and terminates the
 * program.
 *
 * This function attempts to open the error file and reads the error message at
 * the specified index. The error message is then printed to the standard output
 * (stdout), and the program is terminated with a failure status.
 *
 * @param[in] index The index of the error message to print.
 *
 * @return void.
 */
void throw_err(const int index);

#endif  // !ERROR_HANDLING_H
