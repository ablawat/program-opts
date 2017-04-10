#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>

#include "status.h"
#include "options.h"

/* Main Program Options */
options_t program_options;

/*
** Function: options_init
** ----------------------
** Initializes 'program_options'
*/
void options_init(void)
{
    /* Clear all options arguments */
    for (int i = 0; i < OPT_ARGS_NUM; i++)
    {
        program_options.arguments[i] = NULL;
    }
    
    /* Clear all options status */
    program_options.status = 0;
}

/*
** Function: options_get
** ---------------------
** Reads all command-line options into 'program_opts'
*/
status_t options_get(int argc, char **argv, char *error_option)
{
    /* Set default return status */
    status_t status = STATUS_OK;
    
    /* Check output parameter */
    if (error_option != NULL)
    {
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
                                status = STATUS_ERROR_UNRECOGNIZED_OPTION;
                                break;
                    
                    /* Option with missing argument was passed */
                    case ':':   *error_option = optopt;
                                status = STATUS_ERROR_MISSING_OPTION_ARG;
                                break;
                    
                    /* Unsupported option was passed */
                    default:    *error_option = result;
                                status = STATUS_ERROR_UNSUPPORTED_OPTION;
                }
            }
            else
            {
                /* End of options */
                is_next_opt = false;
            }
        }
    }
    else
    {
        /* Set argument error */
        status = STATUS_ERROR_INCORRECT_ARGUMENT;
    }
    
    return status;
}

/*
** Function: is_set_option_a
** ----------------------
** Checks if option 'a' is set
*/
inline bool is_set_option_a()
{
    bool status = false;
    
    if (program_options.status & OPT_A)
    {
        status = true;
    }
    
    return status;
}

/*
** Function: is_set_option_b
** ----------------------
** Checks if option 'b' is set
*/
inline bool is_set_option_b()
{
    bool status = false;
    
    if (program_options.status & OPT_B)
    {
        status = true;
    }
    
    return status;
}

/*
** Function: is_set_option_c
** ----------------------
** Checks if option 'c' is set
*/
inline bool is_set_option_c()
{
    bool status = false;
    
    if (program_options.status & OPT_C)
    {
        status = true;
    }
    
    return status;
}

/*
** Function: is_set_option_d
** ----------------------
** Checks if option 'd' is set
*/
inline bool is_set_option_d()
{
    bool status = false;
    
    if (program_options.status & OPT_D)
    {
        status = true;
    }
    
    return status;
}

/*
** Function: is_set_option_e
** ----------------------
** Checks if option 'e' is set
*/
inline bool is_set_option_e()
{
    bool status = false;
    
    if (program_options.status & OPT_E)
    {
        status = true;
    }
    
    return status;
}

/*
** Function: get_option_arg_d
** ----------------------
** Returns pointer to option 'd' argument
*/
inline char * get_option_arg_d()
{
    return program_options.arguments[OPT_D_ARG];
}

/*
** Function: get_option_arg_e
** ----------------------
** Returns pointer to option 'e' argument
*/
inline char * get_option_arg_e()
{
    return program_options.arguments[OPT_E_ARG];
}
