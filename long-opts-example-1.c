#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>

/* List of available command-line options */
enum
{
    OPT_A = 0x01,  /* Option '-a' and '--opta', bit 0 */
    OPT_B = 0x02,  /* Option '-b' and '--optb', bit 1 */
    OPT_C = 0x04   /* Option '-c' and '--optc', bit 2 */
};

int main(int argc, char **argv)
{
    /*
    ** String containing the legitimate option characters
    **
    ** The first colon character (':') enables detection of missing option argument
    ** Each single character is an short option (ex. 'a' enables '-a' option)
    ** Each single character followed by a colon is a short option that requires an argument (ex. 'c:')
    */
    char optstring[] = ":abc:";
    
    /* Variable containing bit flags for options */
    uint8_t options = 0x00;
    
    /* Pointer to '-c' and '--optc' option argument */
    char *opt_c_arg = NULL;
    
    /* Definitions of long command-line options */
    struct option longopts[] =
    {
        {"opta", no_argument,       NULL, 'a'},  /* Option '--opta' joined with '-a' */
        {"optb", no_argument,       NULL, 'b'},  /* Option '--optb' joined with '-b' */
        {"optc", required_argument, NULL, 'c'},  /* Option '--optc' joined with '-c' */
        {0, 0, 0, 0}                             /* Termination entry */
    };
    
    int result;
    
    do
    {
        /* Read next command-line option */
        result = getopt_long(argc, argv, optstring, longopts, NULL);
        
        switch (result)
        {
            /* Option '-a' or '--opta'  was passed */
            case 'a':   options |= OPT_A;
                        break;
            
            /* Option '-b' or '--optb'  was passed */
            case 'b':   options |= OPT_B;
                        break;
            
            /* Option '-c' or '--optc'  was passed */
            case 'c':   options |= OPT_C;
                        opt_c_arg = optarg;
                        break;
            
            /* Unrecognized option was passed */
            case '?':   if (optopt != 0)
                        {
                            fprintf(stderr, "Error: Unrecognized option '-%c'\n", optopt);
                        }
                        else
                        {
                            fprintf(stderr, "Error: Unrecognized option '%s'\n", argv[optind - 1]);
                        }
                        
                        return 1;
            
            /* Option that requires an argument was passed, but an argument is missing */
            case ':':   if (*(argv[optind - 1] + 1) != '-')
                        {
                            fprintf(stderr, "Error: Option '-%c' requires an argument\n", optopt);
                        }
                        else
                        {
                            fprintf(stderr, "Error: Option '%s' requires an argument\n", argv[optind - 1]);
                        }
                        
                        return 1;
        }
    }
    while (result != -1);
    
    /* Checks if bit flag for option '-a' and '--opta' is set */
    if (options & OPT_A)
    {
        puts("Option '-a' or '--opta' is set");
    }
    
    /* Checks if bit flag for option '-b' and '--optb' is set */
    if (options & OPT_B)
    {
        puts("Option '-b' or '--optb' is set");
    }
    
    /* Checks if bit flag for option '-c' and '--optc' is set */
    if (options & OPT_C)
    {
        printf("Option '-c' or '--optc' is set with argument '%s'\n", opt_c_arg);
    }
    
    return 0;
}
