//
// Created by Cobeasta on 10/2/2023.
//
#include "parse_input.h"

//special characters:
// | > >> < << && ||

#define delims " \"|<>"


int parse_line(char *line, char **parts, int index);

static int IndexOfAny(char *str, int start_index, char toFind[]) {

    int i, j;

    int len = strlen(str);
    int len_delims = strlen(toFind);

    for (i = start_index; i <= len; i++) // for each character in string
    {
        if (str[i] == '\0') {
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


usr_cmd_t parse_input(char *line) {
    int bufsize = 16; // size of commands to be input
    char **parts = malloc(sizeof(char *) * bufsize); // array of string parts of command input

    int argc = parse_line(line, parts, 0);

    char *cmd = parts[0]; // command is first argument
    char **args = parts;

    usr_cmd_t parsed_cmd = {
            .cmd = cmd,
            .argv = args,
            .argc = argc
    };
    return parsed_cmd;
}

int parse_line(char *line, char **parts, int index) {

    printf("Parsing: %s index %d\n\r", line, index);
    int token_index = IndexOfAny(line, 0, delims); // end of token, exclusive

    printf("\tFound delimiter index %d\n\r", token_index);

    if (token_index == -1) // no delimiter found
    {
        parts[index] = malloc(sizeof(char) * (strlen(line) + 1));
        parts[index] = line;
        return index;
    } else if (strcmp(line, "") == 0) {
        printf("\tEmpty string: %s exiting\n\r", line);
        return index;
    }
    char token = line[token_index]; // token that separates. Used to determine behavior
    if (token == '\0') {
        printf("\tFound null character at %d \n\r\t", token_index);
        //parts[index] = malloc(sizeof(char) * (token_index + 2));
        //parts[index] = strncpy(parts[index], line, token_index);
        //parts[index][token_index] = '\0';
        return ++index;
    } else if (token == ' ') // delimited by space, if within quotes ignore. Otherwise, start new token
    {
        printf("\tFound space delimiter\n\r");
        if (token_index == 0) {
            return parse_line(++line, parts, index);
        }
        parts[index] = malloc(sizeof(char) * (token_index + 1));
        parts[index] = strncpy(parts[index], line, token_index);
        parts[index][token_index] = '\0';
        return parse_line((line + token_index + 1), parts, ++index);


    } else if (token == '\"') // enter quotes, new token
    {
        int i_start = token_index + 1;
        int i_end = IndexOfAny(line, i_start, "\"");
        printf("\tFound start and end quote: %d - %d\n\r", i_start, i_end);
        if (i_end == -1) {
            fprintf(stderr, "\tUnmatched quotes in user input");
            USR_ERR = 1;
            return -1;
        } else {
            // found end of string argument
            parts[index] = malloc(sizeof(char) * (token_index + 1));
            parts[index] = strncpy(parts[index], (line + i_start), i_end - i_start);
            parts[index][i_end - i_start] = '\0';
            return parse_line(line + i_end + 1, parts, ++index);
        }
    }
    fprintf(stdout, "\tImproperly reached end of string!");

    return index;
}
