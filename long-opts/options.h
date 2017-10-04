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
typedef enum options_cmd_opt
{
    /* Options with Required Argument */
    OPTION_D = 0x01,    /* Option '-d' and '--optd', bit 0 */
    OPTION_E = 0x02,    /* Option '-e' and '--opte', bit 1 */
    
    /* Options without Argument */
    OPTION_A = 0x04,    /* Option '-a' and '--opta', bit 2 */
    OPTION_B = 0x08,    /* Option '-b' and '--optb', bit 3 */
    OPTION_C = 0x10     /* Option '-c' and '--optc', bit 4 */
}
option_t;

/* Command-Line Options with Required Argument */
enum
{
    OPTION_D_ARG,       /* Option's '-d' and '--optd' argument */
    OPTION_E_ARG,       /* Option's '-e' and '--opte' argument */
    
    OPTION_ARGS_NUM     /* Number of options with argument */
};

#define OPTION_STR_SIZE 3U

/*
** Type: options_conf_t
** --------------------
** Command-Line Options Definition
*/
typedef struct options_conf
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
typedef struct options_data
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

/* Get Program Command-Line Options */
result_t options_get     (int argc, char **argv);

/* Get Option Status */
bool     options_is_set  (option_t option);

/* Get Option Argument */
char *   options_get_arg (option_t option);

#endif
