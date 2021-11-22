#include <unistd.h>
#include <stdio.h>

int main()
{  
    
    char buf[40];
    char *ret = getcwd(buf, 40);

    printf("this is buf : %s\nthis is return : %s\n", buf, ret);
}