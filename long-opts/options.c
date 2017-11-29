#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "options.h"

/* Program Options Definition */
static const options_conf_t program_options_config =
{
    /*
    ** String containing short option characters
    ** -----------------------------------------
    ** The first colon character (':') enables detection of missing option argument
    ** Each single character defines one short option (ex. 'a' enables '-a' option)
    ** Each single character followed by a colon is a short option that requires an argument (ex. 'd:')
    */
    ":ab:ef:",

    /*
    ** Array containing long options definitions
    ** -----------------------------------------
    ** Each string defines one long option name (ex. 'opta' enables '--opta' option)
    ** Each single character links long option with short option (ex. '-a' is linked with '--opta')
    ** The last entry is a termination entry, which is mandatory
    */
    (struct option [])
    {
        { "opte", no_argument,       NULL, 'e'        },    /* Long option 'opte', short 'e' */
        { "optf", required_argument, NULL, 'f'        },    /* Long option 'optf', short 'f' */
        { "optc", no_argument,       NULL, LONG_OPT_C },    /* Long option 'optc' */
        { "optd", required_argument, NULL, LONG_OPT_D },    /* Long option 'optd' */
        { 0, 0, 0, 0 }
    }
};

/* Program Options Data */
static options_data_t program_options_data =
{
    /* Clear options arguments */
    { NULL, NULL },

    /* Clear options bit flags */
    UINT64_C(0),

    /* Init short option string */
    { '-', '\0', '\0' }
};

/* Program Error Option */
const char * options_erropt = NULL;

/* TBD */
int options_argind = 0U;

/*
** Function: options_get
** ---------------------
** Reads Command-Line Options into Program Options Data
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

        /* Read next command-line option */
        int next_option = getopt_long(argc, argv, short_options, long_options, NULL);

        /* Next option has been read */
        if (next_option != -1)
        {
            /* Process option */
            switch (next_option)
            {
                /* Option '-a' was passed */
                case 'a':
                {
                    program_options_data.status |= UINT64_C(1) << OPTION_A;
                    break;
                }

                /* Option '-b' was passed */
                case 'b':
                {
                    program_options_data.status |= UINT64_C(1) << OPTION_B;
                    program_options_data.arguments[OPTION_B_ARG] = optarg;
                    break;
                }

                /* Option '-e' or '--opte' was passed */
                case 'e':
                {
                    program_options_data.status |= UINT64_C(1) << OPTION_E;
                    break;
                }

                /* Option '-f' was passed */
                case 'f':
                {
                    program_options_data.status |= UINT64_C(1) << OPTION_F;
                    program_options_data.arguments[OPTION_F_ARG] = optarg;
                    break;
                }

                /* Option '--optc' was passed */
                case LONG_OPT_C:
                {
                    program_options_data.status |= UINT64_C(1) << OPTION_C;
                    break;
                }

                /* Option '--optd' was passed */
                case LONG_OPT_D:
                {
                    program_options_data.status |= UINT64_C(1) << OPTION_D;
                    program_options_data.arguments[OPTION_D_ARG] = optarg;
                    break;
                }

                /* Unrecognized option was passed */
                case '?':
                {
                    if (optopt != 0)
                    {
                        /* Set short error option */
                        program_options_data.short_option[1] = optopt;
                        options_erropt = program_options_data.short_option;
                    }
                    else
                    {
                        /* Set long error option */
                        options_erropt = argv[optind - 1];
                    }

                    /* Set return status to error */
                    result = RESULT_ERROR_UNRECOGNIZED_OPTION;

                    /* End options parsing */
                    is_next_opt = false;

                    break;
                }

                /* Option with missing argument was passed */
                case ':':
                {
                    if (*(argv[optind - 1] + 1) != '-')
                    {
                        /* Set short error option */
                        program_options_data.short_option[1] = optopt;
                        options_erropt = program_options_data.short_option;
                    }
                    else
                    {
                        /* Set long error option */
                        options_erropt = argv[optind - 1];
                    }

                    /* Set return status to error */
                    result = RESULT_ERROR_MISSING_OPTION_ARG;

                    /* End options parsing */
                    is_next_opt = false;

                    break;
                }

                /* Unsupported option was passed */
                default:
                {
                    if (optopt != 0)
                    {
                        /* Set short error option */
                        program_options_data.short_option[1] = (char)(next_option);
                        options_erropt = program_options_data.short_option;
                    }
                    else
                    {
                        /* Set long error option */
                        options_erropt = argv[optind - 1];
                    }

                    /* Set return status to error */
                    result = RESULT_ERROR_UNSUPPORTED_OPTION;

                    /* End options parsing */
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

    options_argind = optind;

    return result;
}

/*
** Function: options_is_set
** ------------------------
** Checks If Option Was Recognized on Command-Line
*/
bool options_is_set(option_t option)
{
    bool option_status = false;

    if (program_options_data.status & (UINT64_C(1) << option))
    {
        option_status = true;
    }

    return option_status;
}

/*
** Function: options_get_arg
** -------------------------
** Returns Pointer to Option Argument
*/
char * options_get_arg(option_t option)
{
    char *option_argument = NULL;

    if (option < OPTION_ARGS_NUM)
    {
        option_argument = program_options_data.arguments[option];
    }

    return option_argument;
}
