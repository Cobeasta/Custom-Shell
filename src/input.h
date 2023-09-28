#ifndef INPUT_H
#define INPUT_H

/*---INCLUDES---*/
#include <stdio.h>  // standard IO
#include <string.h> // string manipulation
#include <unistd.h> // posix standard
#include <stdlib.h> // type conversions, memory allocations, algorithms, ...
#include<fcntl.h> // file control
#include <errno.h> // error numbers
/*---IMPORTS---*/
#include "shell.h"

/*---PROTOTYPES---*/
void input_init(shell_cfg_t * cfg);
int getinput(FILE * in_stream);



#endif