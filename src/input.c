#include "input.h"
#include <unistd.h> // posix standard


// clear completely empties screen using a control sequence
// CSI command (control sequence introducer starts with ESC[ followed by parameters
// Cursor home position (\033[H) then erase in display (\033[J) from cursor to end of screen
#define clear() printf("\033[H\033[J")

// config as set in shell.c
shell_cfg_t *s_cfg;




/*
 * Provide a greeting message for starting the shell
 */
void input_init(shell_cfg_t *cfg)
{
    s_cfg = cfg;
    clear();

    printf("\n\n\n\nCoby's CPR E 308 Shell\n");
    printf("User:\t%s", s_cfg->username);
}

int getinput(FILE *in_stream)
{
    char *buf = malloc(32 * sizeof(char)); // buffer for reading
    char bufchar;
    int in_size = 64, in_len = 0;
    char *user_input = malloc(in_size * sizeof(char)); // string representing user command

    // flags to change input behavior
    int f_escape, f_tab = 0;

    size_t nbytes;
    ssize_t bytes_read = 0;

    // read file,
    while (fgets(buf, sizeof(buf), in_stream) != NULL && (bytes_read = strlen(buf))&& bytes_read > 0) //successfully read some bytes
    {
        if ((in_len + bytes_read) > in_size)
        {
            in_size *= 2; // double input size if the input is too short
            user_input = realloc(user_input, sizeof(char) * in_size); //reallocate space for input size
        }
         bufchar = * buf; // Character at start of buffer
        switch(bufchar)
        {
            case '\n':
                if(f_escape)
                {

                }
                else
                {

                }
                break;
            case '\\':

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
