
#include "shell.h"


#define opt_promptID 0

// PROTOTYPES


void shell_interactive();

void parse_terminal_args(int argc, char *argv[]);

void sig_handler(int);

// DATATYPES
typedef struct option
{
    int arg_id;
    char *short_name;
    char *long_name;
} opt_t;

enum shell_state s_state = INPUT;
int FLAG_EXIT_CLEAN = 0;
// Default config for shell
shell_cfg_t config = {
        .prompt = "308sh ",
        .username = NULL,
        .max_commands = 100,
        .max_letters = 1000,
        .CDPATH = "~"
};

// Available options for shell
opt_t options[] = {
        {opt_promptID, "p", "prompt"}};

int main(int argc, char *argv[])
{
    // configure interrupt behavior
    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "Failed to register interrupt for SIGINT");
        exit(1);
    }
    if (signal(SIGTERM, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "Failed to register interrupt for SIGTERM");
        exit(1);
    }
    if (signal(SIGCHLD, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "Failed to register interrupt for SIGCHILD");
        exit(1);
    }

    // Get shell process information
    config.username = getlogin();

    parse_terminal_args(argc, argv);
    // start interactive
    shell_interactive();

    exit(0);
}

void shell_interactive()
{
    char *user_input = (char *) NULL;
    usr_cmd_t *usr_in_cmd = NULL;
    s_state = INPUT;
    int ucmd_status;
    input_init(&config);
    execute_init();
    internal_init(&config);
    printf("Starting\n\r");

    while (1)
    {
        // Checks for current shell process
        if (FLAG_EXIT_CLEAN == 1)
        {
            input_close();
            execute_close();
            exit(ucmd_status);
        } else if (s_state == INPUT)
        {
            user_input = malloc(sizeof(char) * config.max_letters); //get space for line

            int result = input_get(&user_input);
            // TODO add to history
            if (result == 0 && strlen(user_input) > 0)
            {

                s_state = PARSE;
            } else
            {
                printf("did not return correctly\n\r");
                free(user_input);
                user_input = NULL;

                s_state = INPUT;
                continue;
            }

        } else if (s_state == PARSE)
        {
            if (user_input == NULL)
            {
                s_state = INPUT;
                continue;
            }
            usr_in_cmd = parse_input(user_input);

            // free space for line
            free(user_input);
            user_input = NULL;

            s_state = EXECUTE;
        } else if (s_state == EXECUTE)
        {
            execute_cmd(*usr_in_cmd, &ucmd_status);
            s_state = INPUT;
        } else if (s_state == WAIT)
        {

        } else if (s_state == FINISHED)
        {
            s_state = INPUT;
        }
        else
        {
            fprintf(stderr, "issue state: %d", s_state);
            exit(1);
        }


    }

}


void parse_terminal_args(int argc, char *argv[])
{
    int i;
    char *newprompt;
    for (i = 0; i < argc; i++)
    {
        if (strcmp("-p", argv[i]) == 0 && argv[i + 1] != NULL)
        {
            size_t len = strlen(argv[i + 1]) + 2; // one for null, one for space
            config.prompt = malloc(len);
            printf(" stuff\n\r");
            sprintf(config.prompt, "%s ", argv[i + 1]);
        }
    }
/*
    size_t opt_ct = 1;
    size_t opt_index, opt_search_index;
    int opt_long; // flag for whether option is long or short. 0 = short, 1 = long
    char *optI;   // current option in iteration

    // parse all arguments
    for (opt_index = 1; opt_index < argc && strcmp(argv[opt_index], "-") != 0; opt_index++) {
        opt_long = 0;           // Default short option
        optI = (argv)[opt_index]; // Get option value
        if (optI[1] == '-')     // if long option
        {
            optI++; // Make option look like short option.
            opt_long = 1;
        }
        opt_search_index = 0;
        // iterate over options
        for (; opt_search_index < opt_ct; opt_search_index++) {
            opt_t opt = options[opt_search_index];
            if ((opt_long == 0 && strcmp((optI + 1), opt.short_name) != 0) ||
                (opt_long == 1 && strcmp((optI + 1), opt.long_name) != 0)) // Long option
            {
                switch (opt.arg_id) {
                    case opt_promptID:
                        config.prompt = (argv)[opt_index];
                        break;
                    default: // option  does not exist TODO err out
                        break;
                }
            }
        }
    }*/
}

void sig_handler(int sig)
{
    switch (sig)
    {
        case SIGINT:
            input_handle_interrupt(sig);
            RECV_SIG_INT = 1;
            break;
        case SIGSEGV:
            fprintf(stderr, "Backtrace of something\n\r");
            break;
        case SIGTERM:
            fprintf(stderr, "Received termination signal\n\r");
            break;
        case SIGCHLD:
            execute_child_exit();
            break;
        default:
            fprintf(stderr, "SOMETHING WEIRD HAPPENED\n\r");
            break;
    }
}

usr_cmd_t *init_cmd(int bufsize)
{
    usr_cmd_t *parsed = malloc(sizeof(usr_cmd_t)); // allocate space for user's command
    parsed->argc = 0;
    parsed->argv = malloc(sizeof(char *) * bufsize); // array of string parts of command input
    return parsed;
}
