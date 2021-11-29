#include <stdio.h>

int main()
{
    char *front = "aaaab";
    char *back = "aae";

    int i = 0;
    
    while(front[i] != 0 && back[i] != 0)
    {
        printf("start : ");
        printf("%c %c\n", front[i], back[i]);
        if(front[i] < back[i])
        {
            printf("end : ");
            printf("%c %c %d", front[i], back[i], i);
            break;
        }
        ++i;
    }
}