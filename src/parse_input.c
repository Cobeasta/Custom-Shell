//
// Created by Cobeasta on 10/2/2023.
//
#include "parse_input.h"

//special characters:
// | > >> < << && ||

#define delims " \"|<>"

int q_flag = 0;

int parse_line(char *line, char ** parts, int index);

static int IndexOfAny(char *str, int start_index, char toFind[]) {

    int i, j;

    int len = strlen(str);
    int len_delims = strlen(delims);

    for (i = start_index; i < len; i++) // for each character in string
    {
        for (j = 0; j < len_delims; j++) // for each possible delimiter
        {
            if (str[i] == delims[j]) // if the character at that index is a delimiter
            {
                return i;
            }
        }
    }
    return -1;
}



usr_cmd_t parse_input(char * line)
{
    int bufsize = 32; // size of commands to be input
    char **parts = malloc(sizeof(char *) * bufsize); // array of string parts of command input

    q_flag = 0; // flag for finding quotes
    int argc = parse_line(line, parts, 0);

    char * cmd = parts[0]; // command is first argument
    char ** args = parts;

    usr_cmd_t parsed_cmd = {
            .cmd = cmd,
            .argv = args,
            .argc = argc
    };
    return parsed_cmd;
}

int parse_line(char *line, char ** parts, int index)
{

    int token_index = IndexOfAny(line, 0, delims); // end of token, exclusive
    char token = line[token_index]; // token that separates. Used to determine behavior

    if(strcmp(line, ""))
    {

        return index;
    }

    if (q_flag == 0 && token == ' ') // delimited by space, if within quotes ignore. Otherwise, start new token
    {
        parts[index] = strncpy(parts[0], line, (token_index - 0)); // copy into parts arrayvoid parse_line(char *line, char ** parts, int index)

        parse_line((line + token_index + 1), parts, ++index);
    }
    else if(q_flag == 0 && token == '\"') // enter quotes, new token
    {
        parts[index++] = strncpy(parts[0], line, (token_index - 0)); // copy into parts arrayvoid parse_line(char *line, char ** parts, int index)

        int i_start = token_index + 1;
        int i_end = IndexOfAny(line, i_start, "\"");
        if(i_end == -1)
        {
            fprintf(stderr, "Unmatched parenthesis in user input");
            USR_ERR = 1;
            return -1;
        }
        else
        {
            // found end of string argument
            parts[index] = strncpy(parts[index], (line + i_start), i_end - i_start);
            parse_line(line + i_end + 1, parts, ++index);
        }

    }
    fprintf("Reached end of parse_line weirdly!");

    return index;
}
