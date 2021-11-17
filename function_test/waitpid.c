#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
     int status, cpid1, cpid2, endpid;

     if((cpid1 = fork()) == 0)
     {
         printf("\t1 : child process:%d\n", getpid());
         sleep(2);
         printf("\t3 : child end\n");
         exit(0);
     }

    
     if((cpid2 = fork()) == 0)
     {
         printf("\t2 : child2 process:%d\n", getpid());
         sleep(4);
         printf("\t5 : child2 end\n");
         exit(0);
     }

     endpid=waitpid(cpid1, &status, 0);
     printf("4 : pid : %d\n", endpid);


     endpid=waitpid(cpid2, &status, 0);
     printf("6 : pid : %d\n", endpid);

     
     printf("7 : parent end\n");
}

// 프로세스가 어떻게 돌아가냐면
// fork로 자식 1, 자식 2 만들고 부모는 endpid=waitpid(cpid1, &status, 0);
// 일로가서 자식1을 기다려 자식 1, 자식 2 상관없이 병렬적 실행
// pid1 실행하고 출력하고 sleep(2) + pid2 실행하고 출력하고 sleep(4)
// pid1 child end >> printf 끝난 자식의 pid출력
// pid2 sleep(4)끝나고 child end2 출력하고 > 끝난 자식의 pid2출력
// 마지막으로 부모 종료 문구 출력



int main()
{
     int status, cpid1, cpid2, endpid;

     if((cpid1 = fork()) == 0)
     {
         printf("\t2 : child process:%d\n", getpid());
         sleep(2);
         printf("\t3 : child end\n");
         exit(0);
     }

    
     if((cpid2 = fork()) == 0)
     {
         printf("\t1 : child2 process:%d\n", getpid());
         sleep(4);
         printf("\t4 : child2 end\n");
         exit(0);
     }

     endpid=waitpid(cpid2, &status, 0);
     printf("5 : pid : %d\n", endpid);

    endpid=waitpid(cpid1, &status, 0);
     printf("6 : pid : %d\n", endpid);

     
     printf("7 : parent end\n");
}

//fork 1 fork 2
//wait 2, wait 1 하여도
//child 1이 먼저 출력
//자원 회수의 순서인듯(wait)

// fork함수를 사용하면 부모에서 나온 자식은 병렬적으로 실행이 되어진다.
// cpid1을 먼저 fork하였으니까 1번 child가 먼저 실행 // 부모, 1번 자식 실행중
// 부모는 이와동시에 cpid2로 자식 2번 생성
// 2번 child 실행 // 부모, 1번 자식, 2번 자식 실행중

// 부모 1번자식 2번 자식 병렬적으로 실행이 되어지고 자식이 종료가 되어서 자원을 회수한다는 함수
// waitpid를 써주면 그 위치에서 자식 1이든 자식2든 종료가 되었고, 명시한 자식의 자원을 회수한다.
// 마지막 7번으로 부모가 종료가 된다.
