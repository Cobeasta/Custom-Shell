//
// Created by Cobeasta on 10/2/2023.
//

#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H

#include "shell.h"


/*---TYPES---*/
/**
 *
 */
typedef struct cmd {
    char * cmd;
    int argc;
    char ** argv;
} usr_cmd_t;



/*---PROTOTYPES---*/
// parse a string line into a command
usr_cmd_t parse_input(char * line);

#endif //PARSE_INPUT_H
