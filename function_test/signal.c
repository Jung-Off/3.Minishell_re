// #include <stdio.h>
// #include <unistd.h>
// #include <signal.h>

// void(*old_fun)(int);

// void sigint_handler(int signo)
// {
//     printf("ctrl-c\n");

//     signal(SIGINT, old_fun);
// }

// int main()
// {
//     old_fun = signal(SIGINT, sigint_handler);
//     while(1)
//     {
//         printf("umumum\n");
//         sleep(1);
//     }
// }

#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

 
void interruptHandler(int sig){
        printf("this program will be exited in 3 seconds..\n");
        sleep(3);
        exit(0);
}
int main()
{

        signal(SIGINT, interruptHandler);        
        printf("input Ctrl+C\n");
        while(1);

        
        // printf("input Ctrl+C\n");
        // sleep(10);
        // signal(SIGINT, interruptHandler);
        // 이 경우에는 signal을 제어할 수 없다!


        // printf("input Ctrl+C\n");
        // signal(SIGINT, interruptHandler);
        // sleep(10);
        
}
