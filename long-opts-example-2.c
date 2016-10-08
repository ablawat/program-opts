#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <stdbool.h>

/* List of available command-line options */
enum
{
    OPT_A = 0x01,  /* Option '-a' and '--opta', bit 0 */
    OPT_B = 0x02,  /* Option '-b' and '--optb', bit 1 */
    OPT_C = 0x04,  /* Option '-c' and '--optc', bit 2 */
    OPT_D = 0x08,  /* Option '-d' and '--optd', bit 3 */
    OPT_E = 0x10   /* Option '-e' and '--opte', bit 4 */
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
    
    /*
    ** Array of long options definitions
    **
    ** Each entry defines one long option and links it to corresponding short option
    */
    struct option options_long[] =
    {
        {"opta", no_argument,       0, 'a'},  /* Long option name 'opta', short name 'a' */
        {"optb", no_argument,       0, 'b'},  /* Long option name 'optb', short name 'b' */
        {"optc", no_argument,       0, 'c'},  /* Long option name 'optc', short name 'c' */
        {"optd", required_argument, 0, 'd'},  /* Long option name 'optd', short name 'd' */
        {"opte", required_argument, 0, 'e'},  /* Long option name 'opte', short name 'e' */
        {0, 0, 0, 0}                          /* Termination entry */
    };
    
    while (true)
    {
        /* Read next command-line option */
        int result = getopt_long(argc, argv, optstring, options_long, NULL);
        
        /* If all options has beed read */
        if (result == -1)
        {
            /* Terminate processing */
            break;
        }
        
        /* Process option */
        switch (result)
        {
            /* Option '-a' or '--opta' was passed */
            case 'a':   options |= OPT_A;
                        break;
            
            /* Option '-b' or '--optb' was passed */
            case 'b':   options |= OPT_B;
                        break;
            
            /* Option '-c' or '--optc' was passed */
            case 'c':   options |= OPT_C;
                        break;
            
            /* Option '-d' or '--optd' was passed */
            case 'd':   options |= OPT_D;
                        opt_d_arg = optarg;
                        break;
            
            /* Option '-e' or '--opte' was passed */
            case 'e':   options |= OPT_E;
                        opt_e_arg = optarg;
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
            
            /* Unsupported option was passed */
            default:    if (optopt != 0)
                        {
                            fprintf(stderr, "Error: Unsupported option '-%c'\n", result);
                        }
                        else
                        {
                            fprintf(stderr, "Error: Unsupported option '%s'\n", argv[optind - 1]);
                        }
                        
                        return 1;
        }
    }
    
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
        puts("Option '-c' or '--optc' is set");
    }
    
    /* Checks if bit flag for option '-d' and '--optd' is set */
    if (options & OPT_D)
    {
        printf("Option '-d' or '--optd' is set with argument '%s'\n", opt_d_arg);
    }
    
    /* Checks if bit flag for option '-e' and '--opte' is set */
    if (options & OPT_E)
    {
        printf("Option '-e' or '--opte' is set with argument '%s'\n", opt_e_arg);
    }
    
    /* Print argv-elements that are not an options */
    for (int i = optind; i < argc; i++)
    {
        printf("No option argument '%s'\n", argv[i]);
    }
    
    return 0;
}
