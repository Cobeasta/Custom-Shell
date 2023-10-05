//
// Created by Cobeasta on 10/4/2023.
//

#include "execute_cmds.h"



int remove_process(pid_t pid);


cmd_exe_t * head_cmd = NULL;
cmd_exe_t * current_cmd = NULL;


int execute_init()
{


    return 0;

}

int execute_cmd(usr_cmd_t cmd, int *status)
{
    pid_t pid;
    if(strcmp(cmd.name, "exit") == 0)
    {
        *status = 0;
        FLAG_EXIT_CLEAN = 1;
        return 0;
    }
    else if(strcmp(cmd.name, "pid"))
    {
        pid_t result = getpid();
        printf("%d\n\r", result);
        return 0;
    }
    else if(strcmp(cmd.name, "ppid"))
    {
        pid_t result = getppid();
        printf("%d\n\r", result);
        return 0;
    }
    fun_call_t fun = internal_find(cmd);

    // Create command object
    cmd_exe_t *cmd_exe = malloc(sizeof(cmd_exe_t));
    cmd_exe->status = status;

    // if we need to expand capacity for more commands

    if (strcmp(fun.name, INTERNAL_CMD_NOTFOUND) == 0)
    {
        printf("Could not find matching internal command\n\r");
        // Not an internal command, check is file for command exists,
        // try running external command
    } else
    {
        // Found internal command
        pid = fork();
        if (pid == -1) // if fork failed
        {
            // fork failed
            fprintf(stderr, "Error in fork\n\r");
        } else if (pid == 0) // if in child process
        {
            // if running internal, do that function
            *status = fun.cmd_fn(cmd);
            exit(*status); // exit with status of that function
            // if external command, execve that
            // in child
        }
    }
    if (pid > 0) // if we are in parent process
    {
        (*cmd_exe).pid = pid;

        if (cmd.bg == 0) // if run in foreground
        {
            s_state = WAIT;
            waitpid(pid, status, 0); // wait and suspend until child is done
            s_state = FINISHED;
            return pid;
        } else if (cmd.bg == 1) // if be command should run in background
        {
            if(head_cmd == NULL)
            {
                head_cmd = cmd_exe;
                current_cmd = head_cmd;
            }
            else
            {
                //start at head
                current_cmd = head_cmd->next;
                // find last command
                while(current_cmd -> next != NULL)
                {
                    current_cmd = current_cmd -> next;
                }
                // insert new command
                current_cmd->next = cmd_exe;
            }
            return pid; // return pid of child process
        }
    }


}
void execute_child_exit()
{
    pid_t pid;
    int * wstat;

    int saved_errno = errno;
    int exit_status;
    while(1)
    {
        // waitpid returns 0 if no children changed state
        // returns PID of terminated child whose state changed
        pid = waitpid((pid_t)(-1), &exit_status, WNOHANG);
        if(pid == -1)
        {
            fprintf(stderr, "Error in child exit handler");
            break;
        }
        else if(pid == 0)
        {
            fprintf(stderr, "No child's state changed\n\r");
            return;
        }
        else
        {
            fprintf(stderr, "Process with pid %d exited\n\r", pid);
            remove_process(pid);
        }
    }
}
int remove_process(pid_t pid)
{
    if(head_cmd == NULL)
    {
        return -1;
    }
    else
    {
        //start at head
        current_cmd = head_cmd;
        cmd_exe_t * next_cmd = current_cmd -> next;
        // Find the command before the one with the "right" pid
        while(next_cmd != NULL && next_cmd->pid != pid)
        {
         current_cmd = current_cmd -> next; // next command is still in last
         next_cmd = current_cmd -> next;
        }
        if(next_cmd == NULL)
        {
            return -1; // did not find pid
        }
        if(next_cmd -> next != NULL) // if node exists after in linked list
        {
            current_cmd -> next = current_cmd -> next -> next; // current node skips removed pid
        }
        // insert new command
        free(current_cmd -> next); // free the pointer to the finished cmd
    }
    // insert new command
}

void execute_interrupt()
{

}
void execute_close()
{

}