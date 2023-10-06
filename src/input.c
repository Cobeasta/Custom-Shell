//
// Created by Cobeasta on 10/6/2023.
//

#include "input.h"

#define flush() while((getchar()) != '\n')

shell_cfg_t * input_cfg;
char ** history;
int history_size;

int input_init(shell_cfg_t *cfg)
{
    input_cfg = cfg;

    history = malloc(sizeof(char *) * input_cfg -> max_commands);
    if(history == NULL)
    {
        fprintf(stderr, "Error getting space for history");
        return 1;
    }
    history_size = 0;
    return 0;
}
int input_get(char ** line)
{

    size_t bufsize;
    ssize_t buflen = -1;
    char * buf = NULL;
    size_t line_len = strlen(*line);
    printf("%s ", input_cfg->prompt);
    fflush(stdout);
    while(buflen <= 0 || *line[line_len] == '\\')
    {
        bufsize = getline(&buf, &bufsize, stdin);
        if(bufsize == -1)
        {
            if(errno == EINTR)
            {
                printf("^c\n");
                return 1;
            }
            else
            {
                printf("ERR\n\r");
            }

        }

        if(bufsize + line_len > input_cfg->max_letters)
        {
            free(buf);
            return 1;
        }
        buflen = strlen(buf);
        buf[buflen - 1] = '\0';
        strcat(*line, buf);

        // free resources
        free(buf);
        buf =  NULL;
        bufsize = -1;
    }

    return 0;

}
int input_close()
{
    free(history);
}

int input_handle_interrupt()
{
    printf("\n");
    RECV_SIG_INT = 0;
    return 0;
}