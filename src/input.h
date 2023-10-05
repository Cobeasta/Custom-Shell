#ifndef INPUT_H
#define INPUT_H

/*---IMPORTS---*/
#include "shell.h"

/*---INCLUDES---*/
#include <readline/readline.h> // package for fancily reading lines


/*---PROTOTYPES---*/
void input_init(shell_cfg_t * cfg);
char *  input_get(char * line);
void input_handle_interrupt(int signo);
/**
 * Free input memory.
 */
void input_close();




#endif