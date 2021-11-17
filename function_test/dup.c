
// 함수 이름에서도 알 수 있듯이 무엇을 복제 한다는 함수입니다. 무엇을 복제 할까요? 바로 파일 서술자!

// dup
// #include <unistd.h>
// int dup(int fd)

// dup는 fd로 전달받은 파일 서술자를 복제하여 반환합니다. dup가 돌려주는 파일 서술자는 가장 낮은 서술자를 반환합니다.
// 성공시 새 파일 서술자.


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    int fd1, fd2;
    char message[32]={"message via fd2\n"};
    fd1 = open("made_by_fd1", O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
    if(fd1 < 0)
    {
        printf("file open error\n");
        exit(0);
    }
    printf("fd2 : %d", fd2);
    fd2 = dup(fd1);
    write(fd2, message, strlen(message));
    printf("fd1 : %d, fd2 : %d\n", fd1, fd2);
    close(fd1);
    close(fd2);
}


