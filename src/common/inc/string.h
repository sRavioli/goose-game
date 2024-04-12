// Copyright (c) 2023 @authors. GNU GPLv3.

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
 * @date 2023-05-17 11:31
 * @version 2.1
 * @copyright GNU GPLv3
 */
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief The maximum allowed length for a string buffer.
 */
#define MAX_BUFFER_LEN 256

/**
 * @brief The default char to use as a filler if the username is too short.
 */
#define FILLER_CHAR "?"

/**
 *  @brief The character that defines a line termination.
 */
#define LINE_END "\n"

/**
 *  @brief The character that defines the end of a string.
 */
#define STR_END '\0'

/**
 *  @brief The character that defines an empty string.
 */
#define STR_EMPTY ""

/**
 *  @brief The default value that a space assumes.
 */
#define SPACE_CHAR ' '

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Concatenates a source string to the end of a buffer string.
 *
 * This function appends the source string to the end of the buffer string. It
 * uses @c snprintf() to safely concatenate the strings, ensuring that the
 * resulting string remains null-terminated.
 *
 * @param[in,out] buffer The buffer string to which the source string is
 *                       appended.
 * @param[in]     source The source string that is concatenated to the buffer
 *                       string.
 *
 * @return void.
 *
 * @note The @e buffer and @e source strings must be null-terminated. It must
 *       have enough space to accommodate the concatenated string, including the
 *       null-terminator.
 */
void concat(char *buffer, const char source[]);

/**
 * @brief Concatenates a source string to the buffer string multiple times.
 *
 * This function appends the source string to the buffer string a specified
 * number of times. The source string is concatenated to the buffer string
 * n_times times using snprintf. The resulting string remains null-terminated.
 *
 * @param[in,out] buffer  The buffer string to which the source string is
 *                        appended.
 * @param[in]     source  The source string that is concatenated to the buffer
 *                        string.
 * @param[in]     n_times The number of times the source string is concatenated.
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
void nconcat(char *buffer, const char source[], const int n_times);

/**
 * @brief Formats a string using a variable argument list and appends it to the
 *        buffer.
 *
 * This function formats a string using a variable argument list and appends it
 * to the end of the buffer string. The format and additional arguments are
 * provided in a similar way as in the @c printf() family of functions. The
 * resulting string remains null-terminated.
 *
 * @param[in,out] buffer      The buffer string to which the formatted string is
 *                            appended.
 * @param[in]     source_size The size of the buffer string.
 * @param[in]     format      The format string used to format the string.
 * @param[in]     va_list     Additional arguments to be formatted into the
 *                            string.
 *
 * @return void.
 *
 * @warning This function does not perform any size checking or memory
 *          allocation! It is the responsibility of the caller to ensure that
 *          the @e buffer has enough space for the formatted string.
 *
 * @note The @e buffer parameter is expected to be a valid pointer to a
 *       null-terminated string and to have enough space to accommodate the
 *       formatted string and its null-terminator.
 * @note The @e source_size parameter specifies the maximum size of the source
 *       string that can be formatted and concatenated to the @e buffer.
 * @note The @e format parameter is expected to be a valid format specifier
 *       string according to the rules of the @c printf() function.
 * @note The <em>variable argument list</em> should correspond to the format
 *       specifier string and provide the values to be formatted.
 *
 * @see @c snprintf() for string formatting.
 * @see @c vsnprintf() for string formatting with a variable argument list.
 */
void fconcat(char *buffer, const int source_size, const char *format, ...);

/**
 * @brief Allocates a character buffer of a specified size and copies a string
 *        into it.
 *
 * This function allocates a character buffer of size (1 + size * strlen(s)) and
 * copies the given string into the buffer. If memory allocation fails, an error
 * is thrown using the throw_err function. The resulting string is
 * null-terminated.
 *
 * @param[in] s    The string to be copied into the allocated buffer.
 * @param[in] size The size of the buffer.
 *
 * @return A pointer to the allocated buffer.
 *
 * @attention The size of the allocated buffer is determined by the size
 *            parameter multiplied by the length of the input character s. It
 *            is important to ensure that the resulting buffer is not too
 *            large to prevent memory overflow.
 *
 * @note The input string @e s should be a valid null-terminated string.
 * @note The @e size parameter specifies the size of the allocated memory for
 *       the copied string, including space for the null terminator.
 * @note The returned pointer points to the dynamically allocated memory and
 *       should be freed by the caller when no longer needed to avoid memory
 *       leaks.
 * @throws STR_ALLOCATION_FAILED_ERROR If the memory allocation fails.
 *
 * @see @c malloc() for memory allocation.
 * @see @c free() for deallocating memory.
 */
char *alloc_char(const char *c, const int size);

/**
 * @brief Allocates memory for a string of the specified size.
 *
 * This function allocates memory for a string of the given size. The allocated
 * memory includes space for the string characters and a null terminator.
 *
 * @param[in] size The size of the string to allocate, excluding the null
 *                 terminator.
 *
 * @return A pointer to the allocated memory block for the string.
 *         It is the responsibility of the caller to free the memory when it
 *         is no longer needed.
 *
 * @throws STR_ALLOCATION_FAILED_ERROR If the memory allocation fails.
 */
char *str_allocate(const int size);

/**
 * @brief Copies a source string to a buffer string.
 *
 * This function copies the source string to the buffer string. It uses snprintf
 * to safely copy the string, ensuring that the resulting string remains
 * null-terminated.
 *
 * @param[out] buffer The buffer string to which the source string is copied.
 * @param[in]  source The source string that is copied to the buffer string.
 *
 * @return void.
 */
void str_copy(char *buffer, const char source[]);

/**
 * @brief Truncates a buffer string to a specified length.
 *
 * This function truncates the buffer string to the specified length. The
 * @c snprintf() function is used to perform the truncation, ensuring that the
 * resulting string is null-terminated.
 *
 * @param[in,out] buffer The buffer string to be truncated.
 * @param[in]     len    The length to which the buffer string is truncated.
 *
 * @return void.
 */
void str_truncate(char *buffer, const int len);

/**
 * @brief Converts a buffer string to uppercase.
 *
 * This function converts each character in the buffer string to uppercase using
 * the @c toupper() function. The resulting string is modified in place.
 *
 * @param[in,out] buffer The buffer string to be converted to uppercase.
 *
 * @return void.
 */
void str_to_uppercase(char *buffer);

#endif  // !STRING_UTILS_H
