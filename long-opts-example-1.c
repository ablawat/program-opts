#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <stdbool.h>

/* Available command-line options */
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
    
    /* Bit flags for options */
    uint8_t options = 0x00;
    
    /* Pointer to '-c' and '--optc' option argument */
    char *opt_c_arg = NULL;
    
    /* Was next option read */
    bool is_next_opt = true;
    
    /*
    ** Array of long options definitions
    **
    ** Each entry defines one long option and links it to corresponding short option
    */
    struct option options_long[] =
    {
        {"opta", no_argument,       0, 'a'},  /* Long option name 'opta', short name 'a' */
        {"optb", no_argument,       0, 'b'},  /* Long option name 'optb', short name 'b' */
        {"optc", required_argument, 0, 'c'},  /* Long option name 'optc', short name 'c' */
        {0, 0, 0, 0}                          /* Termination entry */
    };
    
    while (is_next_opt)
    {
        /* Read next command-line option */
        int result = getopt_long(argc, argv, optstring, options_long, NULL);
        
        /* Next option has been read */
        if (result != -1)
        {
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
        else
        {
            /* End of options */
            is_next_opt = false;
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
        printf("Option '-c' or '--optc' is set with argument '%s'\n", opt_c_arg);
    }
    
    return 0;
}
