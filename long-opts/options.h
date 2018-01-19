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
    OPTION_E,    /* Option '-e' and '--opte' */

    OPTIONS_NUM
}
option_t;

#define OPTIONS_ARGS_NUM      (3U)    /* Number of options with required argument */

#define OPTIONS_LONG_START  (128U)    /* Start identifier for long-only options */
#define OPTIONS_STR_SIZE      (3U)    /* Size of short option string */

#define OPTIONS_STATUS_BIT   (64U)    /* Number of bits in status item */

#define OPTIONS_STATUS_NUM  (((OPTIONS_NUM - 1U) / OPTIONS_STATUS_BIT) + 1U)

/*
** Identifiers for Long Only Options
*/
enum
{
    LONG_OPT_C = (OPTIONS_LONG_START + 0),  /* Long option '--optc' */
    LONG_OPT_D = (OPTIONS_LONG_START + 1)   /* Long option '--optd' */
};

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
result_t  options_parse               (int argc, char **argv);

/* Get Option Status */
bool      options_is_option_set       (option_t option);

/* Get Option Argument */
char *    options_get_option_argument (option_t option);

#endif
