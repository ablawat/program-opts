#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char optstring[] = ":abc:d";
    
    int a_flag = 0;
    int b_flag = 0;
    int d_flag = 0;

    char *c_value = NULL;
    
    int result;
    
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
            
            case 'c':   c_value = optarg;
                        break;
            
            case 'd':   d_flag = 1;
                        break;
            
            case '?':   fprintf(stderr, "Invalid option '-%c'.\n", optopt);
                        return 1;
            
            case ':':   fprintf(stderr, "Option '-%c' requires an argument.\n", optopt);
                        return 1;
        }
    }
    while (result != -1);
    
    printf("Option '-a' = %d\n", a_flag);
    printf("Option '-b' = %d\n", b_flag);
    printf("Option '-d' = %d\n", d_flag);
    
    printf("Option '-c' value = %s\n", c_value);
    
    return 0;
}
