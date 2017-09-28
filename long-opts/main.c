#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "result.h"
#include "options.h"

int main(int argc, char **argv)
{
    char *error_option = NULL;
    
    result_t result = options_get(argc, argv, &error_option);
    
    switch (result)
    {
        case RESULT_ERROR_UNRECOGNIZED_OPTION:
        {
            fprintf(stderr, "Error: Unrecognized option '%s'\n", error_option);
            return 1;
        }
        
        case RESULT_ERROR_MISSING_OPTION_ARG:
        {
            fprintf(stderr, "Error: Option '%s' requires an argument\n", error_option);
            return 1;
        }
        
        case RESULT_ERROR_UNSUPPORTED_OPTION:
        {
            fprintf(stderr, "Error: Unsupported option '%s'\n", error_option);
            return 1;
        }
    }
    
    /* Checks if bit flag for option '-a' and '--opta' is set */
    if (options_is_set(OPTION_A))
    {
        puts("Option '-a' or '--opta' is set");
    }
    
    /* Checks if bit flag for option '-b' and '--optb' is set */
    if (options_is_set(OPTION_B))
    {
        puts("Option '-b' or '--optb' is set");
    }
    
    /* Checks if bit flag for option '-c' and '--optc' is set */
    if (options_is_set(OPTION_C))
    {
        puts("Option '-c' or '--optc' is set");
    }
    
    /* Checks if bit flag for option '-d' and '--optd' is set */
    if (options_is_set(OPTION_D))
    {
        printf("Option '-d' or '--optd' is set with argument '%s'\n", options_get_arg(OPTION_D));
    }
    
    /* Checks if bit flag for option '-e' and '--opte' is set */
    if (options_is_set(OPTION_E))
    {
        printf("Option '-e' or '--opte' is set with argument '%s'\n", options_get_arg(OPTION_E));
    }
    
    return 0;
}
