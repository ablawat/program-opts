#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "result.h"
#include "options.h"

int main(int argc, char **argv)
{
    result_t result = options_parse(argc, argv);

    switch (result)
    {
        case RESULT_ERROR_UNRECOGNIZED_OPTION:
        {
            fprintf(stderr, "Error: Unrecognized option '%s'\n", options_erropt);
            return 1;
        }

        case RESULT_ERROR_MISSING_OPTION_ARG:
        {
            fprintf(stderr, "Error: Option '%s' requires an argument\n", options_erropt);
            return 1;
        }
    }

    /* Checks if bit flag for option '-a' is set */
    if (options_is_option_set(OPTION_A))
    {
        puts("Option '-a' is set");
    }

    /* Checks if bit flag for option '-b' is set */
    if (options_is_option_set(OPTION_B))
    {
        printf("Option '-b' is set with argument '%s'\n", options_get_option_argument(OPTION_B));
    }

    /* Checks if bit flag for option '--optc' is set */
    if (options_is_option_set(OPTION_C))
    {
        puts("Option '--optc' is set");
    }

    /* Checks if bit flag for option '--optd' is set */
    if (options_is_option_set(OPTION_D))
    {
        printf("Option '--optd' is set with argument '%s'\n", options_get_option_argument(OPTION_D));
    }

    /* Checks if bit flag for option '-e' and '--opte' is set */
    if (options_is_option_set(OPTION_E))
    {
        puts("Option '-e' or '--opte' is set");
    }

    /* Checks if bit flag for option '-f' and '--optf' is set */
    if (options_is_option_set(OPTION_F))
    {
        printf("Option '-f or '--optf' is set with argument '%s'\n", options_get_option_argument(OPTION_F));
    }

    /* Print argv-elements that are not an options */
    for (int i = options_argind; i < argc; i++)
    {
        printf("No option argument '%s'\n", argv[i]);
    }

    return 0;
}
