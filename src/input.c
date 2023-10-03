#include "input.h"
#include "shell.h"


// clear completely empties screen using a control sequence
// CSI command (control sequence introducer starts with ESC[ followed by parameters
// Cursor home position (\033[H) then erase in display (\033[J) from cursor to end of screen
#define clear() printf("\033[H\033[J")

// config as set in shell.c
shell_cfg_t *s_cfg;

char * line;

char ** history;
int i_history; // index in history list
/*
 * Provide a greeting message for starting the shell
 */
void input_init(shell_cfg_t *cfg)
{
    s_cfg = cfg;
    line = malloc(sizeof(char) * s_cfg->max_letters); // allocate string for input
    history = malloc(sizeof (char *) * s_cfg -> max_commands); // allocate list for history
    i_history = 0;
    clear();


    //Welcome message
    printf("\n\n\n\nCoby's CPR E 308 Shell\n\r");
    printf("User:\t%s\n\r", s_cfg->username);
}

char * input_get()
{
    // flags to change input behavior
    int f_escape, f_tab = 0;

// buffer for character input.
    char * buf = (char *)  NULL;

    buf = readline(s_cfg -> prompt); // get buf from user

    if(strlen(buf) > 0)
    {
        strcpy(line, buf); // Copy from line's buffer to line to copy
        //TODO check if length of buffer is too big
        free(buf);
    }
    return line;
}

void add_history(char * str)
{
    if(i_history >= s_cfg -> max_commands)
    {

    }

    strcpy(history[i_history], str); // copy string into history
    i_history++;
}

void input_close()
{
    free(line);
    free(history);

}




