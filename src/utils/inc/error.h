#ifndef ERROR_UTILS_H_
#define ERROR_UTILS_H_

/**
 * @brief Print a specific error from a file.
 *
 * This function attempts to open a file, reads the specified error at the given
 * index, and prints it to the standard output (stdout). The file is assumed to
 * contain errors separated by newline characters ('\n'). The function uses a
 * logger for debugging and error logging purposes.
 *
 * @param[in] index The index of the error to be printed. Indexing starts from
 *                  zero.
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
 *                  starts from zero.
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
