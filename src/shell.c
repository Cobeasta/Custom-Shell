#include<shell.h>

typedef option
{
  int 
  char * short_name;
  char * long_name;
}opt_t;

opt_t options[] = [
  { short_name = "p",  long_name = "prompt", value = 0}
]

// Default config for shell
shell_cfg_t config = {
  prompt = "308sh";  
}

int main(int argc, char * argv[])
{
  
  size_t opt_index, opt_search_index;
  char * optI; // current option in iteration
// parse arguments
  for(opt_index = 1; opt_index < argc && argv[opt_index] == '-'; optindex++)
  {
    optI = argv[opt_index]; 
    if(optI[1] == '-') // if long option
    {
      opt_search_index = 0;
      for(;opt_search_index < TODO)
    }
  }
}

