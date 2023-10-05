//
// Created by Cobeasta on 10/4/2023.
//

#include "execute_cmds.h"


int remove_process(pid_t pid);


cmd_exe_t *HEAD = NULL;
cmd_exe_t *current_cmd = NULL;


int execute_init()
{


    return 0;

}
int execute_cmd(usr_cmd_t cmd, int *status)
{
    pid_t pid;

    fun_call_t fun = internal_find(cmd);

    // Create command object
    cmd_exe_t *cmd_exe = malloc(sizeof(cmd_exe_t));
    cmd_exe->status = status;

    // if we need to expand capacity for more commands

    if (fun.cmd_fn == NULL)
    {
        FILE * file;
        struct stat cmd_stat;
        stat(cmd.name, &cmd_stat);
        if(S_ISDIR(cmd_stat.st_mode))
        {
            printf("%s is a dir, not a program", cmd.name);
            return 0;
        }
        pid = fork();

        if (pid == 0) // child process
        {
            int curpid;
            usleep(1);
            curpid = getpid();
            printf("cmd: %s pid: %d started\n\r", cmd.name, curpid);
            *status = execvp(cmd.name, cmd.argv);

            FLAG_EXIT_CLEAN = 1;
            return *status;
        } else if (pid > 0) // parent process
        {
            (*cmd_exe).pid = pid;

            if (cmd.bg == 0) // foreground task
            {
                waitpid(pid, (*cmd_exe).status, 0);
                printf("PID %d exited with status %d\n\r", pid, *status);
                s_state = FINISHED;
                return *cmd_exe->status;
            } else if (cmd.bg == 1) // background task
            {
                // add command to linked-list of commands
                if (HEAD == NULL)
                {
                    HEAD = cmd_exe;
                    current_cmd = HEAD;
                } else
                {
                    //start at head
                    current_cmd = HEAD->next;
                    // find last command
                    while (current_cmd->next != NULL)
                    {
                        current_cmd = current_cmd->next;
                    }
                    // insert new command
                    current_cmd->next = cmd_exe;
                }
                return pid;
            }
        }
    } else
    {
        // Found internal command
        if (cmd.bg == 0)
        {
            *status = fun.cmd_fn(cmd);
            return *status;
        } else if (cmd.bg == 1)
        {
           // todo background internal
        }

    }
}

void execute_child_exit()
{
    pid_t pid;
    int *wstat;

    int saved_errno = errno;
    int exit_status;
    while (1)
    {
        // waitpid returns 0 if no children changed state
        // returns PID of terminated child whose state changed
        pid = waitpid((pid_t) (-1), &exit_status, WNOHANG);
        if (pid == -1 && 10 == errno)
        {
            // no children
            break;
        } else if (pid == -1)
        {
            fprintf(stderr, "Unhandled error in child exit handler");
            printf("\tErrno: %d\n\r", errno);
            break;
        } else if (pid == 0)
        {
            fprintf(stderr, "No child's state changed\n\r");
            return;
        } else
        {
            fprintf(stderr, "Process with pid %d exited\n\r", pid);
            remove_process(pid);
        }
    }
}

int remove_process(pid_t pid)
{
    if (HEAD == NULL)
    {
        return -1;
    } else
    {
        //start at head
        current_cmd = HEAD;
        cmd_exe_t *next_cmd = current_cmd->next;
        // Find the command before the one with the "right" pid
        while (next_cmd != NULL && next_cmd->pid != pid)
        {
            current_cmd = current_cmd->next; // next command is still in last
            next_cmd = current_cmd->next;
        }
        if (next_cmd == NULL)
        {
            return -1; // did not find pid
        }
        if (next_cmd->next != NULL) // if node exists after in linked list
        {
            current_cmd->next = current_cmd->next->next; // current node skips removed pid
        }
        // insert new command
        free(current_cmd->next); // free the pointer to the finished cmd
    }
    // insert new command
}

void execute_interrupt()
{

}

void execute_close()
{

}