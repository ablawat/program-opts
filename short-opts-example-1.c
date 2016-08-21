#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>

/* List of available command-line options */
enum
{
    OPT_A = 0x01,  /* Option '-a', bit 0 */
    OPT_B = 0x02,  /* Option '-b', bit 1 */
    OPT_C = 0x04   /* Option '-c', bit 2 */
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

    /* Pointer to '-c' option argument */
    char *opt_c_arg = NULL;
    
    int result;
    
    /* Disable error messages */
    opterr = 0;
    
    do
    {
        /* Read next command-line option */
        result = getopt(argc, argv, optstring);
        
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
                        opt_c_arg = optarg;
                        break;
            
            /* Unrecognized option was passed */
            case '?':   fprintf(stderr, "Error: Unrecognized option '-%c'\n", optopt);
                        return 1;
            
            /* Option that requires an argument was passed, but an argument is missing */
            case ':':   fprintf(stderr, "Error: Option '-%c' requires an argument\n", optopt);
                        return 1;
        }
    }
    while (result != -1);
    
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
        printf("Option '-c' is set with argument '%s'\n", opt_c_arg);
    }
    
    return 0;
}
