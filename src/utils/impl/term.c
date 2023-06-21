// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "../../globals.h"

#include "../inc/error.h"
#include "../inc/logger.h"
#include "../inc/string.h"

#include "../inc/term.h"

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif /* ifdef _WIN32 */

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

void get_term_size(int *width, int *height) {
  logger.enter_fn(__func__);
#ifdef _WIN32
  logger.log("creating std handle");
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(hConsole, &csbi);

  *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
  logger.log("retrieving terminal informations");
  struct winsize ws;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

  *width = ws.ws_col;
  *height = ws.ws_row;
#endif /* ifdef _WIN32 */
  logger.log("returning width (%i) and height (%i)", *width, *height);
  logger.exit_fn();
}

void clear_screen() {
  logger.enter_fn(__func__);
#ifdef _WIN32
  HANDLE hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD count;
  DWORD cellCount;
  COORD homeCoords = {0, 0};

  hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hStdOut == INVALID_HANDLE_VALUE) {
    logger.log("invalid std handle. returning");
    logger.exit_fn();
    return;
  }
  logger.log("got valid std handle");

  // get the number of cells in the current buffer
  if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
    logger.log("cannot get number of cells of current buffer, returning");
    logger.exit_fn();
    return;
  }
  cellCount = csbi.dwSize.X * csbi.dwSize.Y;

  // fill the entire buffer with spaces
  if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords,
                                  &count)) {
    logger.log("cannot fill buffer with spaces, returning");
    logger.exit_fn();
    return;
  }
  logger.log("cleared screen");

  // fill the entire buffer with the current colors and attributes
  if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount,
                                  homeCoords, &count)) {
    logger.log("can't fill buffer w/ current colors and attributes, returning");
    logger.exit_fn();
    return;
  }

  // move the cursor home
  SetConsoleCursorPosition(hStdOut, homeCoords);

  logger.log("restored screen attributes, colors and cursor");
#else
  logger.log("attempting to clear terminal screen");
  struct winsize ws;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  logger.log("got current window size");

  struct winsize blank_ws = {0};                // Create a blank window size
  ioctl(STDOUT_FILENO, TIOCSWINSZ, &blank_ws);  // Set window size to blank

  // clear
  logger.log("clearing the screen");
  printf("\033[2J");  // Clear the screen
  printf("\033[H");   // Move the cursor to the top-left corner

  ioctl(STDOUT_FILENO, TIOCSWINSZ, &ws);  // Restore original window size
#endif /* ifdef _WIN32 */
  logger.exit_fn();
}

void clear_line() {
  logger.enter_fn(__func__);
#ifdef _WIN32
  logger.log("getting std handle");
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD coord;
  DWORD written;

  GetConsoleScreenBufferInfo(hConsole, &csbi);

  coord.X = 0;
  coord.Y = csbi.dwCursorPosition.Y;
  FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, coord, &written);
  SetConsoleCursorPosition(hConsole, coord);

  logger.log("cleared current line");
#else
  logger.log("attempting to clear line");

  printf("\033[2K");                      // Clear the entire current line
  printf("\r");    // Move the cursor to the beginning of the line
  fflush(stdout);  // Flush the output buffer

  logger.log("line cleared");
#endif /* ifdef _WIN32 */
  logger.exit_fn();
}
