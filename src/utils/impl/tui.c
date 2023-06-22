// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include "../inc/tui.h"
#include "../../globals.h"
#include "../inc/error.h"
#include "../inc/logger.h"
#include "../inc/string.h"
#include "../inc/term.h"

#include <conio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //

void new_screen() {
  logger.enter_fn(__func__);
  clear_screen();

  int term_width, term_heigth;
  get_term_size(&term_width, &term_heigth);
  int left_space = 1 + (term_width - strlen(TITLE_BAR)) * 0.5;

  int i = 0;
  while (i < left_space) {
    printf("%c", CH_SPACE);
    i = i + 1;
  }
  printf(TITLE_BAR, BOLD, RESET);
  logger.log("printed title bar");

  logger.log("printing horizontal separator of width %i", term_width);
  i = 0;
  while (i < term_width) {
    printf("-");
    i = i + 1;
  }
  printf("\n");
  logger.exit_fn();
}

void print_menu(const char filename[]) {
  logger.enter_fn(__func__);
  new_screen();

  logger.log("safe opening file '%s'", filename);
  FILE *fp;
  if (fopen_s(&fp, filename, "r")) {
    logger.log("cannot read from file '%s'", filename);
    logger.stop();
    throw_err(FILE_NOT_READABLE_ERROR);
  }

  int width, height;
  get_term_size(&width, &height);

  // initialize 2D list to store menu entries
  char menu[MAX_MENU_LINES][MAX_BUFFER_LEN];
  char buffer[MAX_BUFFER_LEN];

  int num_lines = 0;  // count number of menu lines
  int max_len = 0;
  // read until EOF or when running out of space
  logger.log("reading from '%s'", filename);
  while (fgets(buffer, MAX_BUFFER_LEN, fp) && num_lines < MAX_MENU_LINES) {
    max_len = max(strlen(buffer), max_len);  // save the longest line

    // copy line to menu list
    snprintf(menu[num_lines], sizeof(buffer), "%s", buffer);
    num_lines = num_lines + 1;
  }
  fclose(fp);

  logger.log("read %i file lines from '%s'", num_lines, filename);

  // print vertical padding
  int i = 0;
  int vert_padding = (height - num_lines - 2) * 0.45;
  while (i < vert_padding) {
    printf("%s", LINE_END);
    i = i + 1;
  }

  // print all menu entries with left padding (center them)
  i = 0;
  int left_padding = (width - max_len) / 2;
  while (i < num_lines) {
    int j = 0;
    while (j < left_padding) {
      printf("%c", CH_SPACE);
      j = j + 1;
    }
    printf("%s", menu[i]);
    i = i + 1;
  }
  printf("%s", LINE_END);

  logger.log("printed menu from '%s'", filename);
  logger.exit_fn();
}

void print_file(const char filename[]) {
  logger.enter_fn(__func__);
  new_screen();

  logger.log("safe opening file '%s'", filename);
  FILE *fp;
  if (fopen_s(&fp, filename, "r")) {
    logger.stop();
    throw_err(FILE_NOT_READABLE_ERROR);
  }

  int width, height;
  get_term_size(&width, &height);

  // read until EOF or when running out of space
  char buffer[MAX_BUFFER_LEN];
  int num_lines = 0;
  logger.log("reading from '%s'", filename);
  while (fgets(buffer, MAX_BUFFER_LEN, fp) && num_lines < MAX_FILE_LINES) {
    printf("%s", buffer);
    num_lines = num_lines + 1;
  }
  fclose(fp);

  logger.log("read %i file lines from '%s'", num_lines, filename);
  logger.exit_fn();
}

int is_back_key(const char key) {
  if (key == ESC || key == ENTER || key == SPACEBAR || key == 'b') {
    return TRUE;
  }
  return FALSE;
}

int is_quit_key(const char key) {
  if (key == ESC || key == 'q') {
    return TRUE;
  }
  return FALSE;
}

void display_file(const char filename[]) {
  logger.enter_fn(__func__);

  print_file(filename);
  printf("%sExit this view by pressing b/ESC/ENTER/SPACEBAR.%s%s", BOLD, RESET,
         LINE_END);

  logger.log("waiting for back key...");
  int display = TRUE;
  while (display) {
    char key = _getch();
    if (is_back_key(key)) {
      display = FALSE;
    }
  }

  logger.log("exiting this view");
  logger.exit_fn();
}

void wait_keypress(const char format[], ...) {
  logger.enter_fn(__func__);

  logger.log("saving args to string buffer");
  char buffer[MAX_BUFFER_LEN] = "";
  concat(buffer, format);

  va_list args;
  va_start(args, format);
  vprintf(buffer, args);
  va_end(args);

  const char spinner[4] = {'|', '/', '-', '\\'};
  printf("  ");

  // display the spinner by printing the char and then deleting it
  logger.log("waiting for a keypress");
  int i = 0;
  while (!_kbhit()) {
    printf("\b");
    printf("%c", spinner[i % sizeof(spinner)]);
    i = i + 1;
    Sleep(100);
  }
  // consume the pressed key before continuing otherwise it will interfere when
  // getting user input.
  _getch();
  logger.log("consumed keypress");
  logger.exit_fn();
}
