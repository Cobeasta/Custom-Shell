#ifndef SHELL_H
#define SHELL_H

/*---IMPORTS---*/
#include <stdio.h> // standard IO with stdin, stderr, stdout
#include <stdlib.h> // type conversions, memory allocations, algorithms, ...
#include <string.h> // string manipulation
#include <unistd.h> // posix standard values
#include <signal.h> // Manipulating signals
#include<fcntl.h> // file control
#include <dirent.h> // directory control
#include <errno.h> // error numbers
#include <sys/types.h> // system datatypes
#include <sys/wait.h> // wait functions for processes
#include <limits.h>
#include <sys/stat.h>
/*---MACROS---*/
#define MAX_COMMANDS = 50;
#define MAX_LETTERS = 1000; // max number of letters per input

/*---TYPES---*/
typedef struct shell_cfg
{
    char *prompt;
    char *username;
    char *CDPATH; // path to check for file path autocompleting
    char *HOME; // path to home dir
    int max_letters; // max number of letters in history
    int max_commands; // max number of commands in history
} shell_cfg_t;

enum shell_state
{
    INPUT, // Reading user input
    PARSE, // Parsing input into command(s)
    EXECUTE, // Executing a command
    WAIT, // Waiting for a command to finish
    FINISHED // finished command, ready  to start next
};

/**
 * Comand format.
 */
typedef struct USR_CMD
{
    char * name;
    char ** argv;
    int argc;
    int bg;
} usr_cmd_t;


/*---PROTOTYPES---*/
usr_cmd_t *init_cmd(int bufsize);


/*---GLOBAL FLAGS---*/
static volatile sig_atomic_t RECV_SIG_TERM = 0;
static volatile sig_atomic_t RECV_SIG_INT = 0;
static volatile sig_atomic_t RECV_SIG_QUIT = 0;

static volatile sig_atomic_t USR_ERR = 0;

extern enum shell_state s_state;

/**
 * When set to 0, the program runs as-is normal.
 * When set to 1, existing shell should exit cleanly
 */
extern int FLAG_EXIT_CLEAN;
/*---IMPORTS---*/

#include "input.h"
#include "parse_input.h"
#include "execute_cmds.h"
#include "internal_cmds.h"
#endif