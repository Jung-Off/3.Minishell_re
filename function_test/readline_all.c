#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

//gcc option
// -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include


void handler(int signum)
{
    if (signum != SIGINT)
		return ;
    write(STDOUT_FILENO, "\n", 1); //개행 찍어주기
	if (rl_on_new_line() == -1)     //update함수에게 개행찍어준거 알리기
		exit(1);
	rl_replace_line("new_ting", 1);      //buffer의 남아있는 문자열 (text)로 바꾸기
                                    //이것을 공백으로 주는 것과 없애는 것 차이가 무엇?
    rl_redisplay();             //바꾼 buffer와 prompt 같이 출력
}

int main()
{
    
    char *str;

    
    signal(SIGINT, handler);
    while(1)
    {   printf("%s", "hello");
        str = readline("prompt : ");
        if(str[0] == 0)
            continue;
        printf("%s\n", str);
        printf("%p\n", str);
        printf("%d\n", str[0]);

        add_history(str);
        free(str);
        str = NULL;
    
        free(str);
    }

}