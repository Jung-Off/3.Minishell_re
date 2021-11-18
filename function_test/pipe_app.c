#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//fd[1] write
//fd[0] read

int main(void)
{
    int fd[2];
    pid_t pid;
    char buf[257];
    int len, status;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    pid = fork();

    //자식 프로세스의 동작 부분이다. fd[1]을 닫는다.
    // 이는 자식 프로세스에서 파이프를 읽기용
    if (pid == 0)
    {
        close(fd[1]); //쓰는 거 닫음
        write(1, "child process:", 15); //표준 출력에 씀
        len = read(fd[0], buf, 256); // 파이프에서 읽어오기
        write(1, buf, len); //읽어온거 표준출력에 쓰기
        close(fd[0]);
    }
    //부모 프로세스의 동작 부분이다. fd[0]을 닫는다. 
    //이는 파이프를 출력
    //용으로 사용하겠다는 의미이다. fd[1]로 문자열을 출력한다.
    else
    {
        close(fd[0]); //부모에서 읽는 거 닫음
        buf[0] = '\0';
        write(fd[1], "test message\n", 14); // 파이프에 씀
        close(fd[1]); //파이프 닫음
        waitpid(pid, &status, 0); //자식 기다림
    }
    return 0;
}
