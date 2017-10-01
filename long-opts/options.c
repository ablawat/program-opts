#define _GNU_SOURCE
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "options.h"

/* Main Program Options Definition */
static const options_conf_t program_options_config =
{
    /*
    ** String containing short option characters
    ** -----------------------------------------
    ** The first colon character (':') enables detection of missing option argument
    ** Each single character defines one short option (ex. 'a' enables '-a' option)
    ** Each single character followed by a colon is a short option that requires an argument (ex. 'd:')
    */
    ":abcd:e:",

    /*
    ** Array containing long options definitions
    ** -----------------------------------------
    ** Each string defines one long option name (ex. 'opta' enables '--opta' option)
    ** Each single character links long option with short option (ex. '-a' is linked with '--opta')
    ** The last entry is a termination entry, which is mandatory
    */
    (struct option [])
    {
        { "opta", no_argument,       0, 'a' },      /* Long option name 'opta', short name 'a' */
        { "optb", no_argument,       0, 'b' },      /* Long option name 'optb', short name 'b' */
        { "optc", no_argument,       0, 'c' },      /* Long option name 'optc', short name 'c' */
        { "optd", required_argument, 0, 'd' },      /* Long option name 'optd', short name 'd' */
        { "opte", required_argument, 0, 'e' },      /* Long option name 'opte', short name 'e' */
        { 0, 0, 0, 0 }
    }
};

/* Main Program Options Data */
static options_data_t program_options_data =
{
    /* Clear options arguments */
    { NULL, NULL },

    /* Clear options bit flags */
    0U,
    
    /* Init short option string */
    { '-', '\0', '\0' }
};

/* Program Options Error Option */
const char * options_erropt = NULL;

/*
** Function: options_get
** ---------------------
** Reads All Command-Line Options into 'program_options_data'
*/
result_t options_get(int argc, char **argv)
{
    /* Set default return status */
    result_t result = RESULT_OK;
    
    /* Was next option read */
    bool is_next_opt = true;
    
    while (is_next_opt)
    {
        const char          *short_options = program_options_config.options_short;
        const struct option *long_options  = program_options_config.options_long;

        /* Read next command-line argument */
        int next_option = getopt_long(argc, argv, short_options, long_options, NULL);
        
        /* Next option has been read */
        if (next_option != -1)
        {
            /* Process option */
            switch (next_option)
            {
                /* Option '-a' or '--opta' was passed */
                case 'a':
                {
                    program_options_data.status |= OPTION_A;
                    break;
                }
                
                /* Option '-b' or '--optb' was passed */
                case 'b':
                {
                    program_options_data.status |= OPTION_B;
                    break;
                }
                
                /* Option '-c' or '--optc' was passed */
                case 'c':
                {
                    program_options_data.status |= OPTION_C;
                    break;
                }
                
                /* Option '-d' or '--optd' was passed */
                case 'd':
                {
                    program_options_data.status |= OPTION_D;
                    program_options_data.arguments[OPTION_D_ARG] = optarg;
                    
                    break;
                }
                
                /* Option '-e' or '--opte' was passed */
                case 'e':
                {
                    program_options_data.status |= OPTION_E;
                    program_options_data.arguments[OPTION_E_ARG] = optarg;
                    
                    break;
                }
                
                /* Unrecognized option was passed */
                case '?':
                {
                    if (optopt != 0)
                    {
                        /* short opt */
                        program_options_data.short_option[1] = optopt;
                        options_erropt = program_options_data.short_option;
                    }
                    else
                    {
                        /* long opt */
                        options_erropt = argv[optind - 1];
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
                        program_options_data.short_option[1] = optopt;
                        options_erropt = program_options_data.short_option;
                    }
                    else
                    {
                        /* long opt */
                        options_erropt = argv[optind - 1];
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
                        program_options_data.short_option[1] = (char)(next_option);
                        options_erropt = program_options_data.short_option;
                    }
                    else
                    {
                        /* long opt */
                        options_erropt = argv[optind - 1];
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
    
    return result;
}

/*
** Function: options_is_set
** ------------------------
** Checks if option is set
*/
bool options_is_set(option_t option)
{
    bool option_status = false;
    
    if (program_options_data.status & option)
    {
        option_status = true;
    }
    
    return option_status;
}

/*
** Function: options_get_arg
** -------------------------
** Returns pointer to option argument
*/
char * options_get_arg(option_t option)
{
    char *option_argument = NULL;

    uint8_t index = ffsll(option) - 1;
    
    if (index < OPTION_ARGS_NUM)
    {
        option_argument = program_options_data.arguments[index];
    }
    
    return option_argument;
}
