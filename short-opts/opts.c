#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#include "status.h"
#include "opts.h"

/* Main Program Options */
options_t program_options;

/*
** Function: options_init
** ----------------------
** Initializes 'program_options'
*/
void options_init(void)
{
    for (int i = 0; i < OPT_ARGS_NUM; i++)
    {
        program_options.arguments[i] = NULL;
    }
    
    program_options.status = 0;
}

/*
** Function: options_get
** ---------------------
** Reads all command-line options into 'program_opts'
*/
status_t options_get(int argc, char **argv, char *error_option)
{
    /* Return value */
    status_t status = STATUS_OK;
    
    /* Initialize options data */
    options_init();
    
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
                case 'a':   program_options.status |= OPT_A;
                            break;
                
                /* Option '-b' was passed */
                case 'b':   program_options.status |= OPT_B;
                            break;
                
                /* Option '-c' was passed */
                case 'c':   program_options.status |= OPT_C;
                            break;
                
                /* Option '-d' was passed */
                case 'd':   program_options.status |= OPT_D;
                            program_options.arguments[OPT_D_ARG] = optarg;
                            break;
                
                /* Option '-e' was passed */
                case 'e':   program_options.status |= OPT_E;
                            program_options.arguments[OPT_E_ARG] = optarg;
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
