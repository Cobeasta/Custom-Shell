#ifndef INPUT_H
#define INPUT_H

/*---INCLUDES---*/
#include <stdio.h>  // standard IO
#include <string.h> // string manipulation
#include <unistd.h> // posix standard
#include <readline/readline.h> // package for fancily reading lines


#include <stdlib.h> // type conversions, memory allocations, algorithms, ...
#include<fcntl.h> // file control
#include <errno.h> // error numbers
/*---IMPORTS---*/
#include "shell.h"


/*---PROTOTYPES---*/
void input_init(shell_cfg_t * cfg);
char *  input_get();
/**
 * Free input memory.
 */
void input_close();




#endif