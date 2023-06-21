#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#define ERROR_FILE "../../../res/text/errors.txt"

#define INVALID_FILENAME_ERROR 1
#define FILE_NOT_WRITABLE_ERROR 2
#define FILE_NOT_READABLE_ERROR 3

#define VALUE_OUT_OF_BOUND_ERROR 4
#define INVALID_INPUT_ERROR 5

#define DUPLICATE_USERNAME_ERROR 6
#define INVALID_USERNAME_ERROR 7

#define ALLOCATION_ERROR 8

#define INVALID_KEY_ERROR 9

#define CALL_STACK_OVERFLOW_ERROR 10
#define CALL_STACK_UNDERFLOW_ERROR 11

// #define FILE_NOT_READABLE_ERROR "failed to read from file '%s'"

void print_err(const int index);
void throw_err(const int index);

#endif  // !ERROR_HANDLING_H
