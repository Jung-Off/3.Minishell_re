
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> //isspace

int main()
{
    char *str;

    while(1)
    {
        str = readline("prompt : ");
        if(str[0] == 0 || isspace(str[0]))
            continue;
        //값이 0은 공백 or 빈칸 일때는 출력하고 싶지 않음

        printf("%s\n", str);
        printf("%p\n", str);
        printf("%d\n", str[0]);

        //  readline은 힙메모리에 저장되기 때문에 다 사용한 메모리는 할달을 해제!
        free(str);
    }
}