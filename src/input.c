#include "input.h"

// clear completely empties screen using a control sequence
// CSI command (control sequence introducer starts with ESC[ followed by parameters
// Cursor home position (\033[H) then erase in display (\033[J) from cursor to end of screen
#define clear() printf("\033[H\033[J")

// config as set in shell.c
shell_cfg_t * s_cfg;
/*
 * Provide a greeting message for starting the shell
 */
void shell_init(shell_cfg_t * cfg)
{
    s_cfg = cfg;
    clear();

    printf("\n\n\n\nCoby's CPR E 308 Shell")
    printf("User:\t%s", s_cfg -> username);

}