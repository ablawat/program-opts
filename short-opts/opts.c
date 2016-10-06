#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#include "status.h"
#include "opts.h"

/* X */
options_t options;

status_t get_opts(int argc, char **argv, char *error_option)
{
    /* Option characters */
    char optstring[] = ":abcd:e:";
    
    /* Return value */
    status_t status = STATUS_OK;
    
    int result;
    
    for (int i = 0; i < OPT_ARGS_NUM; i++)
    {
        options.args[i] = NULL;
    }
    
    options.flags = 0;
    
    /* Disable error messages */
    opterr = 0;
    
    do
    {
        /* Read next command-line argument */
        result = getopt(argc, argv, optstring);
        
        switch (result)
        {
            /* Option '-a' was passed */
            case 'a':   options.flags |= OPT_A;
                        break;
            
            /* Option '-b' was passed */
            case 'b':   options.flags |= OPT_B;
                        break;
            
            /* Option '-c' was passed */
            case 'c':   options.flags |= OPT_C;
                        break;
            
            /* Option '-d' was passed */
            case 'd':   options.flags |= OPT_D;
                        options.args[OPT_D_ARG] = optarg;
                        break;
            
            /* Option '-e' was passed */
            case 'e':   options.flags |= OPT_E;
                        options.args[OPT_E_ARG] = optarg;
                        break;
            
            /* Unrecognized option was passed */
            case '?':   *error_option = optopt;
                        status = STATUS_ERROR1;
                        break;
                        
            /* Option with missing argument was passed */
            case ':':   *error_option = optopt;
                        status = STATUS_ERROR2;
                        break;
        }
    }
    while (result != -1);
    
    return status;
}
