/**
 * @file string.h
 * @brief Header file for string related functions
 *
 * This file contains declarations for functions related to string operations
 * such as concatening two string or more, truncating a string, etc.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-05-01 12:38
 * @version 2.0
 * @copyright GNU GPLv3
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./globals.h"

/**
 * @brief Concatenates a string to a buffer of any type (narrow or wide
 *        character).
 *
 * This function concatenates a string to a buffer of any type (narrow or wide
 * character) based on the type of the buffer pointer. It determines the type of
 * strings to concatenate based on the size of the buffer pointer, and calls the
 * appropriate helper function.
 *
 * @param[in,out] buffer A pointer to the buffer to concatenate to.
 * @param[in]     source A pointer to the string to concatenate.
 *
 * @return void.
 *
 * @warning This function does not perform any type checking on the buffer and
 *          source pointers! It is the caller's responsibility to ensure proper
 *          usage of this function.
 *
 * @note The @e buffer and @e source strings must be null-terminated. It must
 *       have enough space to accommodate the concatenated string, including the
 *       null-terminator. The @e buffer pointer @b must be of either @c char* or
 *       @c wchar_t* type.
 * @note If the @e buffer pointer is not of @c char* or @c wchar_t* type, an
 *       error message will be printed to indicate unsupported values.
 */
void concat(char *buffer, const char *source);

/**
 * @brief Concatenate a source string to the given buffer "n" times.
 *
 * This function appends the contents of the @e source string to the end of the
 * given @e buffer multiple times, as specified by the @c n_times parameter. The
 * @e buffer is updated in-place.
 *
 * @param[in,out] buffer  Pointer to the buffer to concatenate to.
 * @param[in]     source  Pointer to the source string to append.
 * @param[in]     n_times Number of times to concatenate the source string to
 *                        the buffer.
 *
 * @return void.
 *
 * @warning This function does not perform any size checking or memory
 *          allocation! It is responsibility of the caller to ensure that the
 *          @e buffer has enough space for the concatenated string.
 *
 * @note The @e buffer parameter is expected to be a valid pointer to a
 *       null-terminated string. It should have enough space to accommodate the
 *       concatenated strings and their null-terminators.
 * @note The @e source parameter is expected to be a valid pointer to a
 *       null-terminated string.
 *
 * @see @c snprintf() for string formatting.
 */
void nconcat(char *buffer, const char *source, const int n_times);

/**
 * @brief Concatenate a formatted string to the given buffer.
 *
 * This function append the given formatted string to the end of the @e buffer,
 * using the provide format specifier and a <em>variable argument list</em>. The
 * @e buffer is updated in-place.
 *
 * @param[in,out] buffer      Pointer to the buffer to concatenate to.
 * @param[in]     source_size Maximum size of the source string to be formatted
 *                            and concatenated.
 * @param[in]     format      Format specifier string.
 * @param[in]     va_list     Variable argument list to be formatted.
 *
 * @return void.
 *
 * @warning This function does not perform any size checking or memory
 *          allocation! It is the responsibility of the caller to ensure that
 *          the @e buffer has enough space for the formatted string.
 * @note The @e buffer parameter is expected to be a valid pointer to a
 *       null-terminated string and to have enough space to accommodate the
 *       formatted string and its null-terminator.
 * @note The @e source_size parameter specifies the maximum size of the source
 *       string that can be formatted and concatenated to the @e buffer.
 * @note The @e format parameter is expected to be a valid format specifier
 *       string according to the rules of the C @c printf() function.
 * @note The <em>variable argument list</em> should correspond to the format
 *       specifier string and provide the values to be formatted.
 *
 * @see @c snprintf() for string formatting.
 * @see @c vsnprintf() for string formatting with a variable argument list.
 */
void fconcat(char *buffer, const int source_size, const char *format, ...);

/**
 * @brief Allocates memory for a character buffer with null-termination.
 *
 * This function dynamically allocates memory for a character buffer with
 * null-termination. The size of the buffer is determined by the given size
 * parameter and the length of the input character s. The resulting buffer will
 * be null-terminated.
 *
 * @param[in] s    Pointer to the input string to be copied.
 * @param[in] size Size of the allocated memory for the copied string.
 *
 * @return Pointer to the dynamically allocated memory containing the copied
 *         string.
 *
 * @attention The size of the allocated buffer is determined by the size
 *            parameter multiplied by the length of the input character s. It
 *            is important to ensure that the resulting buffer is not too
 *            large to prevent memory overflow.
 * @note The input string s should be a valid null-terminated string.
 * @note The size parameter specifies the size of the allocated memory for the
 *       copied string, including space for the null terminator.
 * @note The returned pointer points to the dynamically allocated memory and
 *       should be freed by the caller when no longer needed to avoid memory
 *       leaks.
 * @note If the memory allocation fails, an error message is printed and the
 *       program exits with a failure status code.
 *
 * @see `malloc()` for memory allocation.
 * @see `free()` for deallocating memory.
 */
char *alloc_char(const char *c, const int size);

/**
 * @brief Copies the contents of the source string to the destination buffer.
 *
 * This function copies the contents of the source string to the destination
 * buffer, ensuring that the buffer is null-terminated.
 *
 * @param[in,out] buffer A pointer to the destination buffer.
 * @param[in]     source A pointer to the source string.
 *
 * @return void.
 *
 * @note The destination buffer must be large enough to hold the entire source
 *       string, including the null terminator.
 */
void str_copy(char *buffer, const char *source);

/**
 * @brief Truncates the buffer at the specified length.
 *
 * This function truncates the contents of the buffer to the specified length,
 * ensuring that the buffer is null-terminated.
 *
 * @param[in,out] buffer A pointer to the buffer to truncate.
 * @param[in]     len    The length at which to truncate the buffer.
 *
 * @return void.
 *
 * @note The buffer must be large enough to hold the entire truncated string,
 *       including the null terminator.
 */
void str_truncate(char *buffer, const int len);

/**
 * @brief Converts a string to uppercase.
 *
 * This function modifies the contents of the buffer by converting all
 * alphabetic characters to uppercase.
 *
 * @param[in,out] buffer A pointer to the string to convert to uppercase.
 *
 * @return void.
 */
void str_to_uppercase(char *source);

#endif  // !STRING_UTILS_H
