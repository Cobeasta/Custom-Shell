#ifndef SHELL_H
#define SHELL_H

/*---IMPORTS---*/
#include<stdio.h>
#include <string.h>
/*---MACROS---*/

/*---PROTOTYPES---*/
typedef struct shell_cfg
{
  char * prompt;
  char * username;
} shell_cfg_t;

/*---IMPORTS---*/
#include "input.h"

#endif