

// int dup2(int fd, int fd2)
// dup2는 새 서술자의 값을 fd2로 지정합니다. 만일 fd2가 이미 열려있으면 fd2를 닫은 후 복제가 됩니다. 역시 성공시
// 새 파일 서술자, 오류시 -1을 반환

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

// int main()
// {
//     int fd1, ret;
//     char message[32]={"STDERR from fd1\n"};
    
//     //그림 1번
//     fd1 = open("made_by_fd1", O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
//     if(fd1 < 0)
//     {
//         printf("file open error\n");
//         exit(0);
//     }
//     //표준 입출력으로 print됨
//     printf("file open\n");

//     //fd1의 파일 디스크립터가 명시한 STDOUT_FILENO의 파일 디스크립터로 복제됨
//     //그림 2번
//     ret = dup2(fd1, STDOUT_FILENO);

//     //fd1으로 출력됨
//     printf("fd1 : %d, ret:%d\n", fd1, ret);

//     //STDERR_FILENO 디스크립터가 명시된 fd1으로 복제됨
//     //그림 3번
//     ret = dup2(STDERR_FILENO, fd1);

//     //fd1은 에러로 출력됨
//     write(fd1, message, strlen(message));

//     //stdout이 file로 써짐
//     printf("printf를 썻지만 파일에 기록됨\n");

//     close(fd1);    
    
// }

int main()
{
    int fd;
    int tmp;
    int ret;
    char buffer[4096];

    tmp = open("made_by_fd1", O_RDONLY);
    fd = dup2(tmp, STDIN_FILENO);
    close(tmp);

    ret = read(STDIN_FILENO, buffer, 4096);

    buffer[ret] = '\0';
    write(STDOUT_FILENO, buffer ,strlen(buffer));
    return (0);
}





