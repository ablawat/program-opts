#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "status.h"
#include "opts.h"

int main(int argc, char **argv)
{
    char error_option;
    
    status_t status = options_get(argc, argv, &error_option);
    
    if (status == STATUS_ERROR1)
    {
        fprintf(stderr, "Error: Unrecognized option '-%c'\n", error_option);
        return 1;
    }
    else if (status == STATUS_ERROR2)
    {
        fprintf(stderr, "Error: Option '-%c' requires an argument\n", error_option);
        return 1;
    }
    else if (status == STATUS_ERROR3)
    {
        fprintf(stderr, "Error: Unsupported option '-%c'\n", error_option);
        return 1;
    }
    
    /* Checks if bit flag for option '-a' is set */
    if (is_set_option_a())
    {
        puts("Option '-a' is set");
    }
    
    /* Checks if bit flag for option '-b' is set */
    if (is_set_option_b())
    {
        puts("Option '-b' is set");
    }
    
    /* Checks if bit flag for option '-c' is set */
    if (is_set_option_c())
    {
        puts("Option '-c' is set");
    }
    
    /* Checks if bit flag for option '-d' is set */
    if (is_set_option_d())
    {
        printf("Option '-d' is set with argument '%s'\n", get_option_arg_d());
    }
    
    /* Checks if bit flag for option '-e' is set */
    if (is_set_option_e())
    {
        printf("Option '-e' is set with argument '%s'\n", get_option_arg_e());
    }
    
    return 0;
}
