//
// Created by Cobeasta on 10/4/2023.
//

#include "internal_cmds.h"

shell_cfg_t *  s_cfg;

int internal_init(shell_cfg_t * cfg)
{
    s_cfg = cfg;

    return 0;

}
int internal_exit(usr_cmd_t usr_cmd);

const fun_call_t internal_functions[] = {
        {
            .name = INTERNAL_CMD_NOTFOUND,
            .cmd_fn = NULL
            }
};
const int fun_count = sizeof(internal_functions);
/**
 * Find internal command from list of internal commands
 * @param cmd
 * @return
 */
fun_call_t internal_find(usr_cmd_t cmd)
{
    int i;
    // iterate through all internal function names
    for(i = 0; i < fun_count; i++)
    {
        if(strcmp(internal_functions[i].name, cmd.name) == 0)
        {
            // Internal function found
            return internal_functions[i];
        }
    }
    // return default function
    return internal_functions[0];
}

int pid()
{
    return getpid();
}

int cd()
{
    char * cdpath = s_cfg.

}
