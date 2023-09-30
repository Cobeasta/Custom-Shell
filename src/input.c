#include "input.h"
#include "shell.h"


// clear completely empties screen using a control sequence
// CSI command (control sequence introducer starts with ESC[ followed by parameters
// Cursor home position (\033[H) then erase in display (\033[J) from cursor to end of screen
//#define clear() printf("\033[H\033[J")

// config as set in shell.c
shell_cfg_t *s_cfg;


void promptLine();


/*
 * Provide a greeting message for starting the shell
 */
void input_init(shell_cfg_t *cfg)
{
    s_cfg = cfg;
    clear();

    printf("\n\n\n\nCoby's CPR E 308 Shell\n\r");
    printf("User:\t%s\n\r", s_cfg->username);
}

char * input_get(FILE *in_stream)
{
    int bufsize = 64, insize = 0;
    char *buf = malloc(bufsize * sizeof(char)); // buffer for reading

    char input;


    // flags to change input behavior
    int f_escape, f_tab = 0;

    size_t nbytes;
    ssize_t bytes_read = 0;

    // read file,
    while ((input = getch())) //successfully read some bytes
    {
        if (interrupted) // receive SIGTERM
        {
            buf = "";
            return buf;
        }
        if ((insize) >= bufsize)
        {
            bufsize *= 2; // double input size if the input is too short
            buf = realloc(buf, sizeof(char) * bufsize); //reallocate space for input size
        }
        switch(input)
        {
            case '\n':
                if(f_escape)
                {
                    // new line on prompt, continue input
                }
                else
                {
                    // return input to main loop
                }
                break;
            case '\\':
                if(f_escape)
                {
                    f_escape = 0;
                    buf[insize++] = input;
                }
                else
                {
                    f_escape = 1;
                }

            default:
                user_input[in_len] = bufchar; //Normal character
                break;
        }
        char in_char = user_input[in_len];

    }
    if(errno == EINTR)
    {
        // Read terminated due to interrupt signal
        //TODO
    }
    else if(errno == EBADF)
    {
        // read terminated, bad file
        //TODO
    }
}

void promptLine()
{

}
