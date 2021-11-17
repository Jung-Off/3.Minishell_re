#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


// 만약 두번째 프로세스가 끝났을때는 그대로 종료하지만 작업이 끝나지 않았을때는 a라는 작업을 해야하는 상황이라면?
// wait은 계속 자식 프로세스가 끝날때까지 block되었는데 waitpid는 옵션을 사용
int main()
{
     int status, cpid1, cpid2, endpid;

     if((cpid1 = fork()) == 0)
     {
         printf("\tchild process:%d\n", getpid());
         sleep(2);
         printf("\tchild end\n");
         exit(0);
     }

    
     if((cpid2 = fork()) == 0)
     {
         printf("\tchild2 process:%d\n", getpid());
         sleep(4);
         printf("\tchild2 end\n");
         exit(0);
     }

    while(1)
    {
        endpid = waitpid(cpid2, &status, 0);
        if (endpid == 0)
        {
            printf("%d %d\n", cpid1, cpid2);
            printf("child2 not finished\n");
            sleep(1);
        }
        else
        {
            break;
        }
        
    }

     printf("parent end\n");
}

// int main()
// {
//      int status, cpid1, cpid2, endpid;

//      if((cpid1 = fork()) == 0)
//      {
//          printf("\tchild process:%d\n", getpid());
//          sleep(4);
//          printf("\tchild end\n");
//          exit(0);
//      }

    
//      if((cpid2 = fork()) == 0)
//      {
//          printf("\tchild2 process:%d\n", getpid());
//          sleep(2);
//          printf("\tchild2 end\n");
//          exit(0);
//      }

//     while(1)
//     {
//         endpid = wait(&status);
//         if (endpid == 0)
//         {
//             printf("child2 not finished\n");
//             sleep(1);
//         }
//         else
//         {
//             break;
//         }
        
//     }
//     printf("end child pid : %d", endpid);
//     //임의 의 종료된 자식 pid를 wait은 가져온다.

//      printf("parent end\n");
// }

