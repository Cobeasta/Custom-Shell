//
// Created by Cobeasta on 10/6/2023.
//

#ifndef CUSTOM_SHELL_INPUT_H
#define CUSTOM_SHELL_INPUT_H

#include "shell.h"

/*---PROTOTYPES---*/
int input_init(shell_cfg_t *cfg);
int input_get(char ** line);
int input_close();
int input_handle_interrupt();

#endif //CUSTOM_SHELL_INPUT_H
