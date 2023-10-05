//
// Created by Cobeasta on 10/4/2023.
//

#include "internal_cmds.h"

int internal_pid(usr_cmd_t cmd);

int internal_ppid(usr_cmd_t cmd);

int internal_cd(usr_cmd_t cmd);

int internal_exit(usr_cmd_t cmd);

int internal_pwd(usr_cmd_t cmd);
int internal_procnam(usr_cmd_t cmd);


shell_cfg_t *input__cfg;

int internal_init(shell_cfg_t *cfg)
{
    input__cfg = cfg;

    return 0;

}

int internal_exit(usr_cmd_t usr_cmd);

const fun_call_t internal_functions[] = {
        {
                .name = INTERNAL_CMD_NOTFOUND,
                .cmd_fn = NULL
        },
        {
                .name = "exit",
                .cmd_fn = internal_exit
        },
        {
                .name = "pid",
                .cmd_fn = internal_pid
        },
        {
                .name = "ppid",
                .cmd_fn = internal_ppid
        },
        {
                .name = "cd",
                .cmd_fn = internal_cd
        },
        {
            .name = "pwd",
            .cmd_fn = internal_pwd
        },
        {
            .name = "procnam",
            .cmd_fn = internal_procnam
        }
};
const int fun_count = 7;

/**
 * Find internal command from list of internal commands
 * @param cmd
 * @return
 */
fun_call_t internal_find(usr_cmd_t cmd)
{

    int i;
    // iterate through all internal function names
    for (i = 1; i < fun_count; i++)
    {
        if (strcmp(internal_functions[i].name, cmd.name) == 0)
        {
            // Internal function found
            return internal_functions[i];
        }
    }
    // return default function
    return internal_functions[0];
}

int internal_pid(usr_cmd_t cmd)
{
    pid_t result = getpid();
    printf("%d\n\r", result);
    return 0;
}

int internal_ppid(usr_cmd_t cmd)
{
    pid_t result = getpid();
    printf("%d\n\r", result);
    return 0;
}

int internal_exit(usr_cmd_t cmd)
{
    FLAG_EXIT_CLEAN = 1;
    return 0;
}

int internal_cd(usr_cmd_t cmd)
{
    if (cmd.argc > 1)
    {
        char *path = cmd.argv[1];
        DIR *dir = opendir(path);
        if (dir != NULL)
        {
            chdir(path);
            closedir(dir);
            printf("\n");
            return 0;
        } else if (ENOENT == errno)
        {
            printf("No such directory\n\r");
            return 1;
        } else
        {
            printf("Could not open directory\n\r");
            return 1;
        }
    }
    //deep copy of cdpath
    char *cdpath = malloc(sizeof(char) * (strlen(input__cfg->CDPATH) + 1));
    strcpy(cdpath, input__cfg->CDPATH);
    char *path_to_check;
    path_to_check = strtok(cdpath, ":"); // split string based on delimiters

    while ((path_to_check = strtok(NULL, ":")) != NULL)
    {
        DIR *dir = opendir(path_to_check);
        if (dir != NULL)
        {
            chdir(path_to_check);
            closedir(dir);
            return 0;
        } else if (ENOENT == errno)
        {
            // directory does not exist, continue
            continue;
        } else
        {
            // directory could not be opened for a different reason
            continue;
        }
    }
    return 1;
}
int internal_pwd(usr_cmd_t cmd)
{
    char cwd[PATH_MAX]; // array of max size for paths
    if(getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n\r", cwd);
        return 0;
    }
    else
    {
        return 1;
    }
}

int internal_procnam(usr_cmd_t cmd)
{

    int pidtofind;
    cmd_exe_t * current_cmd;
    if(cmd.argc > 1)
    {
        pidtofind = atoi(cmd.argv[1]);

    }
    if(HEAD == NULL)
    {
        printf("No child processes\n\r");
        return -1;
    }
    else
    {
        //start at head
        current_cmd = HEAD;
        // Find the command before the one with the "right" pid
        while(current_cmd->pid != pidtofind && current_cmd->next != NULL)
        {
            current_cmd = current_cmd -> next; // Check next node for pid
        }
        if(current_cmd->pid == pidtofind)
        {
            printf("%s\n\r", current_cmd->cmd.name);
            return 0;
        }
        else
        {
            printf("Count not find child process\n\r");
            return 0;
        }
    }
    cmd_exe_t proc;
}

