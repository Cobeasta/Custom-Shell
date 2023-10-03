
#include "shell.h"


#define opt_promptID 0

// PROTOTYPES
void shell_interactive();
void parse_terminal_args(int argc, char *argv[]);
void sig_handler(int);

// DATATYPES
typedef struct option {
    int arg_id;
    char *short_name;
    char *long_name;
} opt_t;

// Default config for shell
shell_cfg_t config = {
        .prompt = "308sh ",
        .username = NULL,
        .max_commands = 100,
        .max_letters = 1000
};

// Available options for shell
opt_t options[] = {
        {opt_promptID, "p", "prompt"}};

int main(int argc, char *argv[]) {
    // configure interrupt behavior
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    // Get shell process information
    config.username = getlogin();
    // start interactive
    shell_interactive();

    exit(0);
}

void shell_interactive() {

    input_init(&config);

    while(1)
    {
        char * user_input = (char *)  NULL;

        if (RECV_SIG_INT) // receive SIGTERM
        {
            input_close();
            exit(0);
        }
        user_input = input_get(stdin);

        usr_cmd_t  in_cmd = parse_input(user_input);

        printf("Command: %s\n\r", in_cmd.cmd);
        printf("Args:\n\r");
        int i;

        for(i = 0; i < in_cmd.argc; i++)
        {
            printf("\tArg %d: %s\n\r", i, in_cmd.argv[i]);
        }

        //TODO add history


    }
    input_get(stdin);

}



void parse_terminal_args(int argc, char *argv[])
{

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
    }
}

void sig_handler(int sig) {
    switch (sig) {
        case SIGINT:
            fprintf(stderr, "Retreived interrupt signal\n\r");
            RECV_SIG_INT = 1;
            break;
        case SIGSEGV:
            fprintf(stderr, "Backtrace of something\n\r");
            break;
        case SIGTERM:
            fprintf(stderr, "Received termination signal\n\r");
            break;
        default:
            fprintf(stderr, "SOMETHING WEIRD HAPPENED\n\r");
            break;
    }
}