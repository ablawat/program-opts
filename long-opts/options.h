#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>
#include <stdint.h>
#include <getopt.h>

#include "result.h"

/*
** Type: option_t
** --------------
** Available Command-Line Options
*/
typedef enum
{
    /* Options with Required Argument */
    OPTION_B,    /* Option '-b'              */
    OPTION_D,    /* Option '--optd'          */
    OPTION_F,    /* Option '-f' and '--optf' */

    /* Options without Argument */
    OPTION_A,    /* Option '-a'              */
    OPTION_C,    /* Option '--optc'          */
    OPTION_E     /* Option '-e' and '--opte' */
}
option_t;

/* Indexes for Options Arguments */
enum
{
    OPTION_B_ARG,       /* Option's '-b' argument              */
    OPTION_D_ARG,       /* Option's '--optd' argument          */
    OPTION_F_ARG,       /* Option's '-f' and '--optf' argument */

    OPTION_ARGS_NUM     /* Number of options with argument */
};

/* Start Identifier */
#define LONG_OPT_START 128U

/* Identifiers for Long Only Options */
enum
{
    LONG_OPT_C = (LONG_OPT_START + 0),  /* Long option '--optc' */
    LONG_OPT_D = (LONG_OPT_START + 1)   /* Long option '--optd' */
};

#define OPTION_STR_SIZE 3U

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
    char      * arguments    [OPTION_ARGS_NUM];     /* Options arguments list */
    uint64_t    status;                             /* Options status flags   */
    char        short_option [OPTION_STR_SIZE];     /* Short error option     */
}
options_data_t;

/*
** Variable: options_erropt
** ------------------------
** Provides Error Option String
*/
extern const char * options_erropt;

/*
** Variable: options_argind
** ------------------------
** Provides No-Option Argument Index
*/
extern int options_argind;

/* Get Program Command-Line Options */
result_t options_get     (int argc, char **argv);

/* Get Option Status */
bool     options_is_set  (option_t option);

/* Get Option Argument */
char *   options_get_arg (option_t option);

#endif
