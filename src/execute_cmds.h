//
// Created by Cobeasta on 10/4/2023.
//

#ifndef CUSTOM_SHELL_EXECUTE_CMDS_H
#define CUSTOM_SHELL_EXECUTE_CMDS_H

/*---IMPORTS---*/
#include "shell.h"
#include "internal_cmds.h"

/*---TYPES---*/
/**
 * Type for commands currently executing
 */
typedef struct executing_cmd
{
    pid_t pid;
    usr_cmd_t cmd;
    int * status;
    struct executing_cmd * next;
} cmd_exe_t;

/*---PROTOTYPES---*/
/**
 * Setup for executing commands
 * @return 0 if successful, nonzero if error
 */
int execute_init();
int execute_cmd(usr_cmd_t cmd, int * stat);
void execute_child_exit();
void execute_close();

extern cmd_exe_t * HEAD;
#endif //CUSTOM_SHELL_EXECUTE_CMDS_H
