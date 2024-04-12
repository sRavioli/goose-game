// Copyright (c) 2023 @authors. GNU GPLv3.
// @authors
//    Amorese Emanuele
//    Blanco Lorenzo
//    Cannito Antonio
//    Fidanza Simone
//    Lecini Fabio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/logger.h"
#include "../inc/string.h"

#include "../inc/error.h"

// print an error from the errors file
void print_err(const int index) {
  logger.enter_fn(__func__);
  logger.log("attempting to open file '%s'", ERROR_FILE);

  FILE *fp;
  if (fopen_s(&fp, ERROR_FILE, "r")) {
    printf("failed to read from file '%s'", ERROR_FILE);
    _fcloseall();  // close all open files if there are any
    logger.stop();
    exit(EXIT_FAILURE);
  }

  int lines = 0;
  char buffer[MAX_BUFFER_LEN];
  do {
    lines = lines + 1;
    if (lines == index) {
      logger.log("reading desired error");
      fgets(buffer, sizeof(buffer), fp);

      // buffer[strlen(buffer) - 1] = '\0';
      logger.log("printing '%s' to stdout", buffer);
      printf("%s", buffer);
      break;
    }
  } while ((fscanf_s(fp, "%*[^\n]"), fscanf_s(fp, "%*c")) != EOF);

  fclose(fp);
  logger.exit_fn();
  return;
}

// print an error fromt the errors file and quit the program
void throw_err(const int index) {
  logger.enter_fn(__func__);
  logger.log("attempting to open file '%s'", ERROR_FILE);

  FILE *fp;
  if (fopen_s(&fp, ERROR_FILE, "r")) {
    printf("failed to read from file '%s'", ERROR_FILE);
    _fcloseall();  // close all open files if there are any
    logger.stop();
    exit(EXIT_FAILURE);
  }

  int lines = 0;
  char buffer[MAX_BUFFER_LEN];
  do {
    lines = lines + 1;
    if (lines == index) {
      logger.log("reading error");
      fgets(buffer, sizeof(buffer), fp);

      // buffer[strlen(buffer) - 1] = '\0';
      logger.log("printing '%s' to stdout", buffer);
      printf("%s", buffer);
      break;
    }
  } while ((fscanf_s(fp, "%*[^\n]"), fscanf_s(fp, "%*c")) != EOF);

  fclose(fp);
  _fcloseall();
  logger.log("terminating program");
  logger.stop();
  exit(EXIT_FAILURE);
}
