#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



void pr_exit(int status)
{
        if(WIFEXITED(status))
            printf("normal termination, exit status = %d\n",WEXITSTATUS(status));
        else if(WIFSIGNALED(status))
            printf("abnormal termination, signal number =%d%s\n",WTERMSIG(status),
                WCOREDUMP(status) ?  "(core file generated)" : "");
        else if(WIFSTOPPED(status))
            printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main()
{
    pid_t pid;
    int status;

    if((pid = fork()) < 0)
    {
        printf("fork error\n");
        exit(0);
    }
    else if(pid == 0)
        exit(7);

    if(wait(&status) != pid)
    {
        printf("wait error\n");
        exit(0);
    }
    
    pr_exit(status);

    if((pid = fork()) < 0)
    {
        printf("fork error\n");
        exit(0);
    }
    else if(pid == 0)
        abort();
    if(wait(&status) != pid)
    {
        printf("wait error\n");
        exit(0);
    }
    pr_exit(status);

    if((pid=fork()) < 0)
    {
        printf("fork erorr\n");
        exit(0);
    }
    else if(pid==0)        // 0으로 나누기 신호
        status /= 0;
 
    if(wait(&status)!=pid)
    {
        printf("wait error\n");
        exit(0);
    }
 
    pr_exit(status);
 
    exit(0);

}