#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

#include "result.h"

/***********************************************************************
**                      Global Type Definitions                       **
***********************************************************************/

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

/* Number of options with required argument */
#define OPTIONS_ARGS_NUM 3U

/***********************************************************************
**                            Global Data                             **
***********************************************************************/

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

/***********************************************************************
**                    Global Function Declarations                    **
***********************************************************************/

/* Get Program Command-Line Options */
result_t  options_parse               (int argc, char **argv);

/* Get Option Status */
bool      options_is_option_set       (option_t option);

/* Get Option Argument */
char *    options_get_option_argument (option_t option);

#endif
