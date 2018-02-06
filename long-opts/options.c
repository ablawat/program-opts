#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <getopt.h>

#include "options.h"

/***********************************************************************
**                     Local Constant Definitions                     **
***********************************************************************/

/* Start identifier for long-only options */
#define OPTIONS_LONG_START   128U

/* Size of short option string */
#define OPTIONS_STR_SIZE       3U

/* Number of bits in status item */
#define OPTIONS_STATUS_BIT    64U

/*
** Size of options status bits array
*/
#define OPTIONS_STATUS_NUM  (((OPTIONS_NUM - 1U) / OPTIONS_STATUS_BIT) + 1U)

/*
** Identifiers for Long Only Options
*/
enum
{
    LONG_OPT_C = (OPTIONS_LONG_START + 0U),  /* Long option '--optc' */
    LONG_OPT_D = (OPTIONS_LONG_START + 1U)   /* Long option '--optd' */
};

/***********************************************************************
**                       Local Type Definitions                       **
***********************************************************************/

/*
** Type: options_conf_t
** --------------------
** Command-Line Options Definition
*/
typedef struct
{
    char           * options_short;    /* Config for short options */
    struct option  * options_long;     /* Config for long options  */
}
options_conf_t;

/*
** Type: options_data_t
** --------------------
** Command-Line Options Data
*/
typedef struct
{
    char      * arguments    [OPTIONS_ARGS_NUM  ];     /* Options arguments list */
    uint64_t    status       [OPTIONS_STATUS_NUM];     /* Options status flags   */
    char        short_option [OPTIONS_STR_SIZE  ];     /* Short error option     */
}
options_data_t;

/*
** Type: options_list_item_t
** -------------------------
** Command-Line Options List Item
*/
typedef struct
{
    int       option_value;    /* Option getopt value */
    option_t  option_id;       /* Option identifier */
}
options_list_item_t;

/*
** Type: options_list_t
** --------------------
** Command-Line Options List
*/
typedef struct
{
    options_list_item_t  options [OPTIONS_NUM];    /* Options array */
}
options_list_t;

/***********************************************************************
**                             Local Data                             **
***********************************************************************/

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

/* Program Options List */
static const options_list_t program_options_list =
{
    (options_list_item_t [])
    {
        { 'a'       , OPTION_A },
        { 'b'       , OPTION_B },
        { 'e'       , OPTION_E },
        { 'f'       , OPTION_F },
        { LONG_OPT_C, OPTION_C },
        { LONG_OPT_D, OPTION_D }
    }
};

/* Program Options Data */
static options_data_t program_options_data =
{
    /* Clear options arguments */
    { NULL, NULL },

    /* Clear options bit flags */
    { UINT64_C(0) },

    /* Init short option string */
    { '-', '\0', '\0' }
};

/* Program Error Option */
const char * options_erropt = NULL;

/* First No-Option Argument */
int options_argind = 0U;

/***********************************************************************
**                    Local Function Declarations                     **
***********************************************************************/

option_t options_search (int option_value);

/***********************************************************************
**                    Global Function Definitions                     **
***********************************************************************/

/*
** Function: options_parse
** -----------------------
** Reads Command-Line Options into Program Options Data
*/
result_t options_parse(int argc, char **argv)
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
            /* Unrecognized option was passed */
            if (next_option == '?')
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

                /* End of options */
                is_next_opt = false;
            }
            else if (next_option == ':')
            {
                /* Option with missing argument was passed */

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

                /* End of options */
                is_next_opt = false;
            }
            else
            {
                /* Find option identifier */
                option_t option = options_search(next_option);

                /* Find option bit location */
                uint16_t status_index = option / OPTIONS_STATUS_BIT;
                uint16_t bit_number   = option % OPTIONS_STATUS_BIT;

                /* Set option bit */
                program_options_data.status[status_index] |= UINT64_C(1) << bit_number;

                if (option < OPTIONS_ARGS_NUM )
                {
                    /* Set option argument */
                    program_options_data.arguments[option] = optarg;
                }
            }
        }
        else
        {
            /* End of options */
            is_next_opt = false;
        }
    }

    /* Set first no-option argument */
    options_argind = optind;

    return result;
}

/*
** Function: options_is_option_set
** -------------------------------
** Checks If Option Was Recognized on Command-Line
*/
bool options_is_option_set(option_t option)
{
    bool is_option_set = false;

    /* Find option bit location */
    uint16_t status_index = option / OPTIONS_STATUS_BIT;
    uint16_t bit_number   = option % OPTIONS_STATUS_BIT;

    /* Get option bit */
    if (program_options_data.status[status_index] & (UINT64_C(1) << bit_number))
    {
        is_option_set = true;
    }

    return is_option_set;
}

/*
** Function: options_get_option_argument
** -------------------------------------
** Returns Pointer to Option Argument
*/
char * options_get_option_argument(option_t option)
{
    char *option_argument = NULL;

    /* Option has required argument */
    if (option < OPTIONS_ARGS_NUM)
    {
        /* Get option argument */
        option_argument = program_options_data.arguments[option];
    }

    return option_argument;
}

/***********************************************************************
**                     Local Function Definitions                     **
***********************************************************************/

/*
** Function: options_search
** ------------------------
** Finds option identifier in options list
*/
option_t options_search(int option_value)
{
    const options_list_item_t *options_list = program_options_list.options;

    uint16_t lower_index = 0U;
    uint16_t upper_index = OPTIONS_NUM - 1U;

    option_t option_id = OPTIONS_NUM;

    while (upper_index >= lower_index)
    {
        uint16_t middle_index = (lower_index + upper_index) / 2U;

        /* Check option value in options list */
        if (option_value == options_list[middle_index].option_value)
        {
            /* Found option identifier in options list */
            option_id = options_list[middle_index].option_id;
            break;
        }
        else
        {
            /* Check value on middle point */
            if (option_value > options_list[middle_index].option_value)
            {
                /* Continue search in upper half of options list */
                lower_index = middle_index + 1U;
            }
            else
            {
                /* Continue search in lower half of options list */
                upper_index = middle_index - 1U;
            }
        }
    }

    return option_id;
}
