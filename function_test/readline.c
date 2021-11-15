// readline은 입력받은 문자열을 저장하고, 그 메모리주소를 반환한다.

//readline 사용
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>


//표쥰입력 대상 gnl
//prompt는 표준입력을 받기 이저넹 보여줄 문구
//prompt NULL > 출력 x 
// 사용자로부터 받은 입력에서 개행문자까지의 문자열을 readline의
//반환값으로 사용, 이때 반환되는 문자열에서는 개행문자는 포함되지 x


int main()
{
    //readline 함수의 리턴값을 저장하기 위해 임의로 포인터
    char *str;

    //readline함수가 호출되면 인자 prompt : 를 터미널에 출력하고 저장할
    //라인을 입력받는다
    str = readline("prompt : ");
    //read함수는 저장한 문자열의 메모리주소를 반환한다.
    printf("%s\n", str);
    printf("%p\n", str);
    printf("%d\n", str[0]);

    //  readline은 힙메모리에 저장되기 때문에 다 사용한 메모리는 할달을 해제!
    free(str);
}