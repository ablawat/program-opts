#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char optstring[] = ":abcd:e:";
    
    int a_flag = 0;
    int b_flag = 0;
    int c_flag = 0;

    char *d_value = NULL;
    char *e_value = NULL;
    
    int result, i;
    
    
    opterr = 0;
    
    do
    {
        result = getopt(argc, argv, optstring);
        
        switch (result)
        {
            case 'a':   a_flag = 1;
                        break;
            
            case 'b':   b_flag = 1;
                        break;
            
            case 'c':   c_flag = 1;
                        break;
            
            case 'd':   d_value = optarg;
                        break;
            
            case 'e':   e_value = optarg;
                        break;
            
            case '?':   fprintf(stderr, "Unrecognized option '-%c'.\n", optopt);
                        return 1;
            
            case ':':   fprintf(stderr, "Option '-%c' requires an argument.\n", optopt);
                        return 1;
        }
    }
    while (result != -1);
    
    printf("Option '-a' = %d\n", a_flag);
    printf("Option '-b' = %d\n", b_flag);
    printf("Option '-c' = %d\n", c_flag);
    
    printf("Option '-d' value = %s\n", d_value);
    printf("Option '-e' value = %s\n", e_value);
    
    for (i = optind; i < argc; i++)
    {
        printf("No option arg = %s\n", argv[i]);
    }
    
    return 0;
}
