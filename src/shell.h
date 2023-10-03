#ifndef SHELL_H
#define SHELL_H

/*---IMPORTS---*/
#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
/*---MACROS---*/
#define MAX_COMMANDS = 50;
#define MAX_LETTERS = 1000; // max number of letters per input

/*---PROTOTYPES---*/
static volatile sig_atomic_t RECV_SIG_TERM = 0;
static volatile sig_atomic_t RECV_SIG_INT = 0;
static volatile sig_atomic_t RECV_SIG_QUIT = 0;
typedef struct shell_cfg
{
  char * prompt;
  char * username;
  int max_letters; // max number of letters in history
  int max_commands; // max number of commands in history
} shell_cfg_t;

/*---IMPORTS---*/
#include "input.h"

#endif