#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <stdbool.h>

/* List of available command-line options */
enum
{
    OPT_A = 0x01,  /* Option '-a', bit 0 */
    OPT_B = 0x02,  /* Option '-b', bit 1 */
    OPT_C = 0x04,  /* Option '-c', bit 2 */
    OPT_D = 0x08,  /* Option '-d', bit 3 */
    OPT_E = 0x10   /* Option '-e', bit 4 */
};

int main(int argc, char **argv)
{
    /*
    ** String containing the legitimate option characters
    **
    ** The first colon character (':') enables detection of missing option argument
    ** Each single character is an short option (ex. 'a' enables '-a' option)
    ** Each single character followed by a colon is a short option that requires an argument (ex. 'd:')
    */
    char optstring[] = ":abcd:e:";
    
    /* Variable containing bit flags for options */
    uint8_t options = 0x00;
    
    /* Pointers to '-d' and '-e' option arguments */
    char *opt_d_arg = NULL;
    char *opt_e_arg = NULL;
    
    /* Disable error messages */
    opterr = 0;
    
    while (true)
    {
        /* Read next command-line argument */
        int result = getopt(argc, argv, optstring);
        
        /* If all options has beed read */
        if (result == -1)
        {
            /* Terminate processing */
            break;
        }
        
        /* Process option */
        switch (result)
        {
            /* Option '-a' was passed */
            case 'a':   options |= OPT_A;
                        break;
            
            /* Option '-b' was passed */
            case 'b':   options |= OPT_B;
                        break;
            
            /* Option '-c' was passed */
            case 'c':   options |= OPT_C;
                        break;
            
            /* Option '-d' was passed */
            case 'd':   options |= OPT_D;
                        opt_d_arg = optarg;
                        break;
            
            /* Option '-e' was passed */
            case 'e':   options |= OPT_E;
                        opt_e_arg = optarg;
                        break;
            
            /* Unrecognized option was passed */
            case '?':   fprintf(stderr, "Error: Unrecognized option '-%c'\n", optopt);
                        return 1;
            
            /* Option that requires an argument was passed, but an argument is missing */
            case ':':   fprintf(stderr, "Error: Option '-%c' requires an argument\n", optopt);
                        return 1;
            
            /* Unsupported option was passed */
            default:    fprintf(stderr, "Error: Unsupported option '-%c'\n", result);
                        return 1;
        }
    }
    
    /* Checks if bit flag for option '-a' is set */
    if (options & OPT_A)
    {
        puts("Option '-a' is set");
    }
    
    /* Checks if bit flag for option '-b' is set */
    if (options & OPT_B)
    {
        puts("Option '-b' is set");
    }
    
    /* Checks if bit flag for option '-c' is set */
    if (options & OPT_C)
    {
        puts("Option '-c' is set");
    }
    
    /* Checks if bit flag for option '-d' is set */
    if (options & OPT_D)
    {
        printf("Option '-d' is set with argument '%s'\n", opt_d_arg);
    }
    
    /* Checks if bit flag for option '-e' is set */
    if (options & OPT_E)
    {
        printf("Option '-e' is set with argument '%s'\n", opt_e_arg);
    }
    
    /* Print argv-elements that are not an options */
    for (int i = optind; i < argc; i++)
    {
        printf("No option argument '%s'\n", argv[i]);
    }
    
    return 0;
}
