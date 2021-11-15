

#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf("HOME = %s\n", getenv("HOME"));
    printf("PATH = %s\n", getenv("PATH"));

    //PATH를 split ":" 으로 쪼개서 저장하기!
    //char ** 여기에 저장하여두기!
    
    printf("USER = %s\n", getenv("USER"));
}
