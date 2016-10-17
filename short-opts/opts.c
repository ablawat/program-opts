#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#include "status.h"
#include "opts.h"

/* Program Options */
options_t options;

status_t get_options(int argc, char **argv, char *error_option)
{
    /* Return value */
    status_t status = STATUS_OK;
    
    /* Initialize options data */
    for (int i = 0; i < OPT_ARGS_NUM; i++)
    {
        options.arguments[i] = NULL;
    }
    
    options.status = 0;
    
    /* Was next option read */
    bool is_next_opt = true;
    
    /* Disable error messages */
    opterr = 0;
    
    while (is_next_opt)
    {
        /* Read next command-line argument */
        int result = getopt(argc, argv, OPTIONS_STR);
        
        /* Next option has been read */
        if (result != -1)
        {
            /* Process option */
            switch (result)
            {
                /* Option '-a' was passed */
                case 'a':   options.status |= OPT_A;
                            break;
                
                /* Option '-b' was passed */
                case 'b':   options.status |= OPT_B;
                            break;
                
                /* Option '-c' was passed */
                case 'c':   options.status |= OPT_C;
                            break;
                
                /* Option '-d' was passed */
                case 'd':   options.status |= OPT_D;
                            options.arguments[OPT_D_ARG] = optarg;
                            break;
                
                /* Option '-e' was passed */
                case 'e':   options.status |= OPT_E;
                            options.arguments[OPT_E_ARG] = optarg;
                            break;
                
                /* Unrecognized option was passed */
                case '?':   *error_option = optopt;
                            status = STATUS_ERROR1;
                            break;
                
                /* Option with missing argument was passed */
                case ':':   *error_option = optopt;
                            status = STATUS_ERROR2;
                            break;
                
                /* Unsupported option was passed */
                default:    *error_option = result;
                            status = STATUS_ERROR3;
            }
        }
        else
        {
            /* End of options */
            is_next_opt = false;
        }
    }
    
    return status;
}
