//
// Created by Cobeasta on 10/2/2023.
//
#include "parse_input.h"

//special characters:
// | > >> < << && ||

#define delims " \"|<>&"

/*---PROTOTYPES---*/

void parse_line(char *line, usr_cmd_t * cmd, int bufsize);

static int IndexOfAny(char *str, int start_index, char toFind[])
{

    int i, j;

    int len = strlen(str);
    int len_delims = strlen(toFind);

    for (i = start_index; i <= len; i++) // for each character in string
    {
        if (str[i] == '\0')
        {
            return i;
        }
        for (j = 0; j < len_delims; j++) // for each possible delimiter
        {
            if (str[i] == toFind[j]) // if the character at that index is a delimiter
            {
                return i;
            }
        }
    }
    printf("last char: %x\n\r", str[i]);
    return -1;
}


usr_cmd_t *parse_input(char *line)
{

    int cmd_bufsize = 16;
    // Initialize parsed command
    usr_cmd_t * parsed;
    parsed = init_cmd(cmd_bufsize);
    // command args are modified to point to user input

    parse_line(line, parsed, cmd_bufsize);

    parsed->name = parsed->argv[0];

    return parsed;
}
// char ** parts int index int bufsize
void parse_line(char *line, usr_cmd_t * cmd, int bufsize)
{

    int token_index = IndexOfAny(line, 0, delims); // end of token, exclusive

    if (token_index == -1) // no delimiter found
    {
        cmd->argv[cmd -> argc] = malloc(sizeof(char) * (strlen(line) + 1));
        cmd->argv[cmd -> argc] = line;
        return;
    } else if (strcmp(line, "") == 0)
    {
        return;
    }
    char token = line[token_index]; // token that separates. Used to determine behavior
    if (token == '\0')
    {
        cmd -> argv[cmd -> argc] = malloc(sizeof(char) * (token_index + 1));
        cmd -> argv[cmd -> argc] = strncpy(cmd -> argv[cmd -> argc], line, token_index);
        cmd -> argv[cmd -> argc][token_index] = '\0';
        cmd -> argc++;
        return;
    } else if (token == ' ') // delimited by space, if within quotes ignore. Otherwise, start new token
    {
        if (token_index == 0)
        {
            return parse_line(++line, cmd, bufsize);
        }
        cmd -> argv[cmd -> argc] = malloc(sizeof(char) * (token_index + 1));
        cmd -> argv[cmd -> argc] = strncpy(cmd ->argv[cmd -> argc], line, token_index);
        cmd -> argv[cmd -> argc][token_index] = '\0';
        cmd -> argc++;
        return parse_line((line + token_index + 1), cmd, bufsize);


    } else if (token == '\"') // enter quotes, new token
    {
        int i_start = token_index + 1;
        int i_end = IndexOfAny(line, i_start, "\"");
        if (i_end == -1)
        {
            fprintf(stderr, "\tUnmatched quotes in user input");
            USR_ERR = 1;
        } else
        {
            // found end of string argument
            cmd -> argv[cmd -> argc] = malloc(sizeof(char) * (i_end - i_start + 1));
            cmd -> argv[cmd -> argc] = strncpy(cmd -> argv[cmd -> argc], (line + i_start), i_end - i_start);
            cmd -> argv[cmd -> argc][i_end - i_start] = '\0';
            return parse_line(line + i_end + 1, cmd, bufsize);
        }
    }
    else if(token == '&')
    {
        if(token_index == 0)
        {

        }
        else
        {
            cmd -> argv[cmd -> argc] = malloc(sizeof(char) * (token_index + 1));
            cmd -> argv[cmd -> argc] = strncpy(cmd ->argv[cmd -> argc], line, token_index);
            cmd -> argv[cmd -> argc][token_index] = '\0';
            cmd -> argc++;
            return;
        }
    }
    fprintf(stdout, "\tImproperly reached end of string!");

    return;
}


