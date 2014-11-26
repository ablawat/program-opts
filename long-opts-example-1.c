#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    char optstring[] = ":abc:";
    
    int a_flag = 0;
    int b_flag = 0;

    char *c_value = NULL;
    
    struct option long_options[] =
    {
        {"opta", no_argument,       0, 'a'},
        {"optb", no_argument,       0, 'b'},
        {"optc", required_argument, 0, 'c'},
        {0, 0, 0, 0}
    };
    
    int result;
    
    
    do
    {
        result = getopt_long(argc, argv, optstring, long_options, NULL);
        
        switch (result)
        {
            case 'a':   a_flag = 1;
                        break;
            
            case 'b':   b_flag = 1;
                        break;
            
            case 'c':   c_value = optarg;
                        break;
            
            case '?':   if (optopt != 0)
                        {
                            fprintf(stderr, "Unrecognized option '-%c'.\n", optopt);
                        }
                        else
                        {
                            fprintf(stderr, "Unrecognized option '%s'.\n", argv[optind - 1]);
                        }
                        
                        return 1;
            
            case ':':   if (*(argv[optind - 1] + 1) != '-')
                        {
                            fprintf(stderr, "Option '-%c' requires an argument.\n", optopt);
                        }
                        else
                        {
                            fprintf(stderr, "Option '%s' requires an argument.\n", argv[optind - 1]);
                        }
                        
                        return 1;
        }
    }
    while (result != -1);
    
    printf("Option '-a' = %d\n", a_flag);
    printf("Option '-b' = %d\n", b_flag);
    
    printf("Option '-c' value = %s\n", c_value);
    
    return 0;
}
