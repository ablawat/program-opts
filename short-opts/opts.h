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

/* Command-line options with argument */
enum
{
    OPT_D_ARG,    /* Option '-d' argument */
    OPT_E_ARG,    /* Option '-e' argument */
    
    OPT_ARGS_NUM  /* Number of option arguments */
};

/* Command-line options */
typedef struct options
{
    char      * arguments[OPT_ARGS_NUM];    /* Arguments for options */
    uint64_t    status;                     /* Bit flags for options */
}
options_t;

status_t get_opts(int argc, char **argv, char *error_option);

#define is_set_opt_a() (options.status & OPT_A)
#define is_set_opt_b() (options.status & OPT_B)
#define is_set_opt_c() (options.status & OPT_C)
#define is_set_opt_d() (options.status & OPT_D)
#define is_set_opt_e() (options.status & OPT_E)

#define get_arg_d() (options.arguments[OPT_D_ARG])
#define get_arg_e() (options.arguments[OPT_E_ARG])

#endif
