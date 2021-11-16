#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        return (1);
    else if (!pid)
    {
        printf("child : i got a pid %d internaly\n", pid);
        usleep(100000);
        printf("child: exiting with code 0\n");
    }
    else if (pid)
    {
        printf("parent: i have a child which pid is %d\n", pid);
        printf("parent: exiting with coid 0\n");
    }
    return (0);

}