//
// Created by Cobeasta on 10/4/2023.
//

#ifndef CUSTOM_SHELL_INTERNAL_CMDS_H
#define CUSTOM_SHELL_INTERNAL_CMDS_H

#include "shell.h"

typedef struct fun_call
{
    char * name; // name of command
    int(*cmd_fn)(usr_cmd_t usr_cmd); //pointer of input function to call
}fun_call_t;

#define INTERNAL_CMD_NOTFOUND "internal_notfound"

/*---PROTOTYPES---*/
int internal_init(shell_cfg_t * cfg);
fun_call_t internal_find(usr_cmd_t cmd);


#endif //CUSTOM_SHELL_INTERNAL_CMDS_H
