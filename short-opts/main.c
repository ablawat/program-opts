#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "status.h"
#include "opts.h"

int main(int argc, char **argv)
{
    char error_option;
    
    status_t status = get_opts(argc, argv, &error_option);
    
    if (status == STATUS_ERROR1)
    {
        fprintf(stderr, "Error: Unrecognized option '-%c'\n", error_option);
        return 1;
    }
    if (status == STATUS_ERROR2)
    {
        fprintf(stderr, "Error: Option '-%c' requires an argument\n", error_option);
        return 1;
    }
    
    /* Checks if bit flag for option '-a' is set */
    if (is_set_opt_a())
    {
        puts("Option '-a' is set");
    }
    
    /* Checks if bit flag for option '-b' is set */
    if (is_set_opt_b())
    {
        puts("Option '-b' is set");
    }
    
    /* Checks if bit flag for option '-c' is set */
    if (is_set_opt_c())
    {
        puts("Option '-c' is set");
    }
    
    /* Checks if bit flag for option '-d' is set */
    if (is_set_opt_d())
    {
        printf("Option '-d' is set with argument '%s'\n", get_arg_d());
    }
    
    /* Checks if bit flag for option '-e' is set */
    if (is_set_opt_e())
    {
        printf("Option '-e' is set with argument '%s'\n", get_arg_e());
    }
    
    return 0;
}
