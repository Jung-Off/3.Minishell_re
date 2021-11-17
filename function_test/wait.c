#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
     int status, cpid, endpid;

     if((cpid = fork()) == 0)
     {
         printf("\tchild process:%d\n", getpid());
         sleep(10);
         printf("\tchild end\n");
         exit(10);
     }

     endpid=wait(&status);
     printf("end pid : %d\n", endpid);
     printf("WIFEXITED : %d\n", WIFEXITED(status));
     printf("WEXITSTATUS : %d\n", WEXITSTATUS(status));
     printf("WIFSIGNALED : %d\n", WIFSIGNALED(status));

     printf("\n");
     printf("parent end\n");
}