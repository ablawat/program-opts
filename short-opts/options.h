#ifndef OPTS_H
#define OPTS_H

#include <stdbool.h>
#include <stdint.h>

#include "status.h"

/* Available command-line options */
enum
{
    OPT_A = 0x01,  /* Option '-a', bit 0 */
    OPT_B = 0x02,  /* Option '-b', bit 1 */
    OPT_C = 0x04,  /* Option '-c', bit 2 */
    OPT_D = 0x08,  /* Option '-d', bit 3 */
    OPT_E = 0x10   /* Option '-e', bit 4 */
};

/* Command-line options with required argument */
enum
{
    OPT_D_ARG,    /* Option '-d' requires argument */
    OPT_E_ARG,    /* Option '-e' requires argument */
    
    OPT_ARGS_NUM  /* Number of options with required argument */
};

/* Short option characters */
#define OPTIONS_STR ":abcd:e:"

/* Command-line options data */
typedef struct options
{
    char      * arguments[OPT_ARGS_NUM];    /* Arguments for options */
    uint64_t    status;                     /* Bit flags for options */
}
options_t;

/* Main Program Options */
extern options_t program_options;

/* Get all command-line options */
status_t options_get(int argc, char **argv, char *error_option);

/* Get option status */
bool is_set_option_a();
bool is_set_option_b();
bool is_set_option_c();
bool is_set_option_d();
bool is_set_option_e();

/* Get option argument */
char * get_option_arg_d();
char * get_option_arg_e();

#endif
