#include "shell.h"
#include <ncurses.h>

#define opt_promptID 0

// PROTOTYPES
void parse_args(int *argc, char **argv[]);
void shell_interactive();
// DATATYPES
typedef struct option
{
  int arg_id;
  char *short_name;
  char *long_name;
} opt_t;

// Default config for shell
shell_cfg_t config = {
    .prompt = "308sh",
    .username = NULL
};

// Available options for shell
opt_t options[] = {
    {opt_promptID, "p", "prompt"}};

int main(int argc, char *argv[])
{
    initscr();
  //parse_args(&argc, &argv);
  shell_interactive();
}

void shell_interactive()
{

    input_init(&config);
}

void get_user_info()
{

}

void parse_args(int *argc, char **argv[])
{
  size_t opt_ct = 1;
  size_t opt_index, opt_search_index;
  int opt_long; // flag for whether option is long or short. 0 = short, 1 = long
  char *optI;   // current option in iteration

  // parse all arguments
  for (opt_index = 1; opt_index < * argc && strcmp(*argv[opt_index], "-"); opt_index++)
  {
    opt_long = 0;           // Default short option
    optI = (* argv)[opt_index]; // Get option value
    if (optI[1] == '-')     // if long option
    {
      optI++; // Make option look like short option.
      opt_long = 1;
    }
    opt_search_index = 0;
    // iterate over options
    for (; opt_search_index < opt_ct; opt_search_index++)
    {
      opt_t opt = options[opt_search_index];
      if ((opt_long == 0 && strcmp((optI + 1), opt.short_name)) ||
              (opt_long == 1 && strcmp((optI +1), opt.long_name))) // Long option
      {
        switch (opt.arg_id)
        {
        case opt_promptID:
          config.prompt = (*argv)[opt_index];
          break;
        default: // option  does not exist TODO err out
          break;
        }
      }
    }
  }
}
