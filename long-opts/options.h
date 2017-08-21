#ifndef OPTS_H
#define OPTS_H

#include <stdbool.h>
#include <stdint.h>
#include <getopt.h>

#include "result.h"

/* Available Command-Line Options */
enum
{
    OPT_A = 0x01,  /* Option '-a' and '--opta', bit 0 */
    OPT_B = 0x02,  /* Option '-b' and '--optb', bit 1 */
    OPT_C = 0x04,  /* Option '-c' and '--optc', bit 2 */
    OPT_D = 0x08,  /* Option '-d' and '--optd', bit 3 */
    OPT_E = 0x10   /* Option '-e' and '--opte', bit 4 */
};

/* Command-Line Options with Required Argument */
enum
{
    OPT_D_ARG,    /* Option '-d' and '--optd' requires argument */
    OPT_E_ARG,    /* Option '-e' and '--opte' requires argument */
    
    OPT_ARGS_NUM  /* Number of options with required argument */
};

/* Short Option Characters */
#define OPTIONS_STR ":abcd:e:"

/*
** Type: options_t
** ---------------
** Options Type for Command-Line Options Data
*/
typedef struct options
{
    char      * arguments[OPT_ARGS_NUM];    /* Arguments for options */
    uint64_t    status;                     /* Bit flags for options */
}
options_t;

/* Main Program Options */
extern options_t program_options;

/* Get all command-line options */
result_t options_get(int argc, char **argv, char **error_option);

/* Get option status */
bool is_set_option_a (void);
bool is_set_option_b (void);
bool is_set_option_c (void);
bool is_set_option_d (void);
bool is_set_option_e (void);

/* Get option argument */
char * get_option_arg_d (void);
char * get_option_arg_e (void);

#endif
