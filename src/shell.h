#ifndef SHELL_H
#define SHELL_H

/*---IMPORTS---*/
#include<stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>
/*---MACROS---*/


/*---PROTOTYPES---*/
static volatile sig_atomic_t interrupted = 0;
typedef struct shell_cfg
{
  char * prompt;
  char * username;
} shell_cfg_t;

/*---IMPORTS---*/
#include "input.h"

#endif