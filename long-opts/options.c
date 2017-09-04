#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "result.h"
#include "options.h"

/* Main Program Options */
options_t program_options;

/*
** Function: options_init
** ----------------------
** Initializes 'program_options' Data
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
** Reads All Command-Line Options into 'program_opts' Data
*/
result_t options_get(int argc, char **argv, char **error_option)
{
    /* Set default return status */
    result_t result = RESULT_OK;
    
    /* Check output parameter */
    if (error_option != NULL)
    {
        /* Initialize options data */
        options_init();
        
        /*
        ** Array of long options definitions
        **
        ** Each entry defines one long option and links it to corresponding short option
        */
        struct option options_long[] =
        {
            {"opta", no_argument,       0, 'a'},  /* Long option name 'opta', short name 'a' */
            {"optb", no_argument,       0, 'b'},  /* Long option name 'optb', short name 'b' */
            {"optc", no_argument,       0, 'c'},  /* Long option name 'optc', short name 'c' */
            {"optd", required_argument, 0, 'd'},  /* Long option name 'optd', short name 'd' */
            {"opte", required_argument, 0, 'e'},  /* Long option name 'opte', short name 'e' */
            {0, 0, 0, 0}                          /* Termination entry */
        };
        
        /* Was next option read */
        bool is_next_opt = true;
        
        while (is_next_opt)
        {
            /* Read next command-line argument */
            int next_option = getopt_long(argc, argv, OPTIONS_STR, options_long, NULL);
            
            /* Next option has been read */
            if (next_option != -1)
            {
                /* Process option */
                switch (next_option)
                {
                    /* Option '-a' or '--opta' was passed */
                    case 'a':
                    {
                        program_options.status |= OPT_A;
                        break;
                    }
                    
                    /* Option '-b' or '--optb' was passed */
                    case 'b':
                    {
                        program_options.status |= OPT_B;
                        break;
                    }
                    
                    /* Option '-c' or '--optc' was passed */
                    case 'c':
                    {
                        program_options.status |= OPT_C;
                        break;
                    }
                    
                    /* Option '-d' or '--optd' was passed */
                    case 'd':
                    {
                        program_options.status |= OPT_D;
                        program_options.arguments[OPT_D_ARG] = optarg;
                        
                        break;
                    }
                    
                    /* Option '-e' or '--opte' was passed */
                    case 'e':
                    {
                        program_options.status |= OPT_E;
                        program_options.arguments[OPT_E_ARG] = optarg;
                        
                        break;
                    }
                    
                    /* Unrecognized option was passed */
                    case '?':
                    {
                        if (optopt != 0)
                        {
                            /* short opt */
                            *error_option = malloc(3);
                            
                            (*error_option)[0] = '-';
                            (*error_option)[1] = optopt;
                            (*error_option)[2] = '\0';
                        }
                        else
                        {
                            /* long opt */
                            *error_option = malloc(strlen(argv[optind - 1]));
                            
                            strcpy(*error_option, argv[optind - 1]);
                        }
                        
                        /* set return status to error */
                        result = RESULT_ERROR_UNRECOGNIZED_OPTION;
                        
                        /* end options parsing */ 
                        is_next_opt = false;
                        
                        break;
                    }
                                
                    /* Option with missing argument was passed */
                    case ':':
                    {
                        if (*(argv[optind - 1] + 1) != '-')
                        {
                            /* short opt */
                            *error_option = malloc(3);
                            
                            (*error_option)[0] = '-';
                            (*error_option)[1] = optopt;
                            (*error_option)[2] = '\0';
                        }
                        else
                        {
                            /* long opt */
                            *error_option = malloc(strlen(argv[optind - 1]));
                            
                            strcpy(*error_option, argv[optind - 1]);
                        }
                        
                        /* set return status to error */
                        result = RESULT_ERROR_MISSING_OPTION_ARG;
                        
                        /* end options parsing */ 
                        is_next_opt = false;
                        
                        break;
                    }
                    
                    /* Unsupported option was passed */
                    default:
                    {
                        if (optopt != 0)
                        {
                            /* short opt */
                            *error_option = malloc(3);
                            
                            (*error_option)[0] = '-';
                            (*error_option)[1] = (char)(next_option);
                            (*error_option)[2] = '\0';
                        }
                        else
                        {
                            /* long opt */
                            *error_option = malloc(strlen(argv[optind - 1]));
                            
                            strcpy(*error_option, argv[optind - 1]);
                        }
                        
                        /* set return status to error */
                        result = RESULT_ERROR_UNSUPPORTED_OPTION;
                        
                        /* end options parsing */ 
                        is_next_opt = false;
                    }
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
        result = RESULT_ERROR_INCORRECT_ARGUMENT;
    }
    
    return result;
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
