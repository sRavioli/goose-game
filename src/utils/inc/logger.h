// Copyright (c) 2023 @authors. GNU GPLv3.

/**
 * @file logger.h
 * @brief Header file for managing logging operations.
 *
 * The @c logger.h file provides definitions and function prototypes for
 * managing logging operations. It defines macros for log formatting, error
 * messages, and stack trace separator. It also declares the @c Logger struct,
 * which encapsulates various logging operations through function pointers.
 * Additionally, it declares functions for starting, stopping, and logging
 * events using the logger, as well as functions for entering and exiting
 * functions and enabling/disabling the logger.
 *
 * Usage Example:
 * @code
 * int main (void) {
 *   logger.enter_fn(__func__);
 *
 *   logger.log("this is an event message: %s", "some data");
 *
 *   logger.stop()
 *   return 0;
 * }
 * @endcode
 *
 * @note The @c __func__ keyword is advised to be used as the function name.
 *
 * @authors
 *    Amorese Emanuele
 *    Blanco Lorenzo
 *    Cannito Antonio
 *    Fidanza Simone
 *    Lecini Fabio
 *
 * @date 2023-05-23 10:31
 * @version 2.5
 * @copyright GNU GPLv3
 */
#ifndef LOGGER_H
#define LOGGER_H

// -------------------------------------------------------------------------- //
// PRE-PROCESSOR MACROS                                                       //
// -------------------------------------------------------------------------- //

/**
 * @brief The format string for the timestamp in log messages.
 *
 * The @c TIMESTAMP_FORMAT macro defines the format string used to represent the
 * timestamp in log messages. It follows the format of "day/month/year
 * hour:minute:second" and is used to format the timestamp for each log entry.
 */
#define TIMESTAMP_FORMAT "%d/%m/%y %H:%M:%S"

/**
 * @brief The banner used in the log file.
 *
 * The @c LOG_BANNER macro represents the banner that is used as a separator or
 * heading in the log file. It consists of a row of equal signs and is used to
 * visually separate different sections of the log file.
 */
#define LOG_BANNER "=================================="

/**
 * @brief The message indicating the start of the log.
 *
 * The @c LOG_START_MSG macro represents the message that is written to the log
 * file at the beginning of logging. It serves as an indicator that the log has
 * started.
 */
#define LOG_START_MSG "START LOG"

/**
 * @brief The message indicating the stop of the log.
 *
 * The @c LOG_STOP_MSG macro represents the message that is written to the log
 * file at the end of logging. It serves as an indicator that the log has
 * stopped.
 */
#define LOG_STOP_MSG "STOP  LOG"

/**
 * @brief The format string for the log banner.
 *
 * The @c LOG_BANNER_FMT macro defines the format string used to format the log
 * banner. It includes placeholders for the log banner itself, which is
 * represented by %s, and additional formatting characters for proper spacing.
 */
#define LOG_BANNER_FMT "%s %s %s\n"

/**
 * @brief The format string for log messages.
 *
 * The @c LOG_MSG_FORMAT macro defines the format string that should be used to
 * format log messages. It includes placeholders for the timestamp, function
 * stack trace, and log message itself. The placeholders are represented as
 * follows:
 *   - %s represents the timestamp
 *   - %s represents the function stack trace
 *   - %s represents the log message
 */
#define LOG_MSG_FORMAT "[%s] %s - %s\n"

/**
 * @brief The maximum depth of the call stack.
 *
 * The @c MAX_CALLSTACK_DEPTH macro defines the maximum depth of the call stack,
 * which represents the number of function calls that can be logged. It is used
 * to allocate memory for the call stack array.
 */
#define MAX_CALLSTACK_DEPTH 20

/**
 * @brief The separator for the stack trace in log messages.
 *
 * The @c STACK_TRACE_SEPARATOR macro represents the separator used between
 * function names in the stack trace of log messages. It is used to visually
 * separate the function names and make the stack trace more readable.
 */
#define STACK_TRACE_SEPARATOR " > "

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @struct Logger
 * @brief Logger structure for managing logging operations.
 *
 * The @c Logger struct defines a set of function pointers that encapsulate
 * various logging operations. This struct provides a convenient way to organize
 * and access logging functionality through function pointers.
 *
 * Usage Example:
 * @code
 * int main (void) {
 *   logger.enter_fn(__func__);
 *
 *   logger.log("this is an event message: %s", "some data");
 *
 *   logger.stop()
 *   return 0;
 * }
 * @endcode
 *
 * @note It is advided to use the @c __func__ keyword as the function name.
 */
struct Logger {
  /**
   * @brief Starts the logger and initializes logging operations.
   *
   * This function pointer is used to start the logger and initialize logging
   * operations. It takes a filename as an argument and sets up the logger to
   * write log events to the specified file.
   *
   * @param[in] filename The name of the log file to be created or opened.
   *
   * @return void.
   */
  void (*start)(const char filename[]);

  /**
   * @brief Logs a formatted message.
   *
   * This function pointer is used to log a formatted message. It takes a format
   * string and variable arguments, similar to the @c printf() function, and
   * logs the formatted message using the underlying logging mechanism.
   *
   * @param[in] format  The format string for the log message.
   * @param[in] va_list Variable arguments to be formatted and logged.
   *
   * @return void.
   */
  void (*log)(const char format[], ...);

  /**
   * @brief Stops the logger and finalizes logging operations.
   *
   * This function pointer is used to stop the logger and finalize logging
   * operations. It performs any necessary cleanup and ensures that all log
   * events are written before the logger is stopped.
   *
   * @return void.
   */
  void (*stop)();

  /**
   * @brief Disables the logger.
   *
   * This function pointer is used to disable the logger. It deactivates the
   * logging functionality, preventing any further log events from being
   * recorded or written to the log file.
   *
   * @return void.
   */
  void (*disable)();

  /**
   * @brief Enables the logger.
   *
   * This function pointer is used to enable the logger. It activates the
   * logging functionality, allowing log events to be recorded and written to
   * the log file.
   *
   * @return void.
   */
  void (*enable)();

  /**
   * @brief Enters a function and logs the entry event.
   *
   * This function pointer is used to enter a function and log the entry event.
   * It takes the name of the calling function as an argument and logs the
   * function entry event, typically including the name of the calling function.
   *
   * @param[in] caller The name of the calling function.
   *
   * @return void.
   */
  void (*enter_fn)(const char caller[]);

  /**
   * @brief Exits a function and logs the exit event.
   *
   * This function pointer is used to exit a function and log the exit event. It
   * logs the function exit event, typically including the name of the function
   * being exited.
   *
   * @return void.
   */
  void (*exit_fn)();
};

/**
 * @brief External declaration of the logger instance.
 *
 * The @c logger variable is an external declaration of the @c Logger struct
 * It allows other source files to access the same instance of the logger,
 * providing a shared logger across multiple modules.
 *
 * Usage Example:
 * @code{.C}
 * int main (void) {
 *   logger.enter_fn(__func__);
 *
 *   logger.log("this is an event message: %s", "some data");
 *
 *   logger.stop();
 *   return 0;
 * }
 * @endcode
 */
extern struct Logger logger;

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

/**
 * @brief Starts the logger and creates a new log file with the specified
 *        filename.
 *
 * This function starts the logger by creating a new log file with the given
 * filename. It first checks if logging is active; if logging is disabled, the
 * function returns without performing any actions. It then validates the
 * provided filename to ensure it is a valid string. If the filename is
 * determined to be invalid, an error is thrown.
 *
 * The function copies the given filename to a static variable for future
 * reference. It then attempts to open the log file in write mode. If the file
 * cannot be opened for writing, an error is thrown. If the file is opened
 * successfully, a log start message is written to the file indicating the start
 * of logging.
 *
 * After successful initialization, the logger is marked as started, and the
 * file is closed.
 *
 * @param[in] filename The name of the log file to be created.
 *
 * @return void.
 */
void start_logger(const char *filename);

/**
 * @brief Stops the logger and appends a log stop message to the log file.
 *
 * This function stops the logger by appending a log stop message to the
 * currently active log file. If the logger is not active or has not been
 * started, the function returns without performing any actions.
 *
 * This function calls the @c exit_fn() function before closing the logger,
 * sparing the inconvenience of calling the latter function. The function
 * attempts to open the log file in append mode. If the file cannot be opened
 * for writing, an error is thrown. If the file is opened successfully, a log
 * stop message is appended to the file to indicate the termination of logging.
 *
 * After writing the log stop message, the file is closed.
 *
 * @return void.
 */
void stop_logger();

/**
 * @brief Logs an event with a formatted message to a log file.
 *
 * This function logs an event by formatting the message using a variadic
 * argument list and writing it to a log file. The logging is conditional based
 * on the state of the logger, and if the logger is not active or not started,
 * the function returns without performing any logging. The event message is
 * constructed based on the given format string and additional arguments.
 *
 * The function also includes the current timestamp, stack trace, and other
 * information in the log message. The timestamp is generated using the current
 * local time. The stack trace is created by concatenating the function call
 * stack, separated by a predefined separator.
 *
 * If the log file cannot be opened for writing, an error is thrown.
 *
 * @param[in] format  The format string for the event message.
 * @param[in] va_list Additional arguments to be formatted into the event
 *                    message.
 *
 * @return void.
 */
void log_event(const char format[], ...);

/**
 * @brief Enters a function and logs the entry event.
 *
 * This inline function is used to enter a function and log the entry event. It
 * takes the name of the calling function as an argument and pushes it onto the
 * call stack. The function then calls the @c log_event function with a
 * formatted message indicating the function entry. The message includes the
 * name of the calling function.
 *
 * @param[in] caller The name of the calling function.
 *
 * @return void.
 */
void enter_fn(const char caller[]);

/**
 * @brief Exits a function and logs the exit event.
 *
 * This inline function is used to exit a function and log the exit event. It
 * calls the @c log_event function with a formatted message indicating the
 * function exit. The message includes the name of the function at the top of
 * the call stack, which is popped from the stack after logging the message.
 *
 * @return void.
 */
void exit_fn();

/**
 * @brief Disables the logger.
 *
 * This inline function is used to disable the logger. It sets the
 * @c is_logger_active flag to @c FALSE, indicating that logging should be
 * disabled. When the logger is disabled, log events will not be recorded or
 * written to the log file.
 *
 * @return void.
 */
void disable_logger();

/**
 * @brief Enables the logger.
 *
 * This inline function is used to enable the logger. It sets the
 * @c is_logger_active flag to @c TRUE, indicating that logging should be
 * enabled. When the logger is enabled, log events will be recorded and written
 * to the log file.
 *
 * @return void.
 */
void enable_logger();

#endif  // !LOGGER_H
