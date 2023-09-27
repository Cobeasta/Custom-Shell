#ifndef SHELL_H
#define SHELL_H

/*---IMPORTS---*/
#include<stdio.h>

/*---MACROS---*/
char * PROMPT;

/*---PROTOTYPES---*/
typedef struct shell_cfg
{
  char * prompt;
} shell_cfg_t;

#endif