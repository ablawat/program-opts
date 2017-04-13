#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "result.h"
#include "options.h"

int main(int argc, char **argv)
{
    char error_option;
    
    result_t result = options_get(argc, argv, &error_option);
    
    switch (result)
    {
        case RESULT_ERROR_UNRECOGNIZED_OPTION:
        {
            fprintf(stderr, "Error: Unrecognized option '-%c'\n", error_option);
            return 1;
        }
        
        case RESULT_ERROR_MISSING_OPTION_ARG:
        {
            fprintf(stderr, "Error: Option '-%c' requires an argument\n", error_option);
            return 1;
        }
        
        case RESULT_ERROR_UNSUPPORTED_OPTION:
        {
            fprintf(stderr, "Error: Unsupported option '-%c'\n", error_option);
            return 1;
        }
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
