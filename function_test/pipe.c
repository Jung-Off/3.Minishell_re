
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ		0
#define WRITE 		1


#define BUFFER_SIZE	4096

void	childcommand(void)
{
	int				ret;
	char			buffer[BUFFER_SIZE];

	ret = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	buffer[ret] = '\0';
	write(STDOUT_FILENO, buffer, strlen(buffer));
}

void	childproc(int pipe[2])
{
	int				fd;
	int				r_fd;
	int				w_fd;

	printf("Child: I'm going to close fd for Read\n");
	printf("Child: I'm going to connect STDOUT to fd for Write\n");
	printf("Child: I'm going to connect STDIN to fd from a file\n");
	printf("Child: Eventually I'll read from STDIN (file) and write to STDOUT (pipe)\n");
	close(pipe[WRITE]);
	w_fd = dup2(pipe[READ], STDOUT_FILENO);
	close(pipe[READ]);
	if (w_fd == -1)
		exit(1);
	fd = open("read.txt", O_RDONLY);
	if (fd == -1)
		exit(1);
	r_fd = dup2(fd, STDIN_FILENO);
	close(fd);
	if (r_fd == -1)
		exit(1);
	childcommand();
}

void parentcommand(void)
{
    int ret;
    char buffer[BUFFER_SIZE];

    ret = read(STDIN_FILENO, buffer, BUFFER_SIZE);
    buffer[ret] = '\0';
    write(STDOUT_FILENO, buffer , strlen(buffer));
}

void parentproc(int pipe[2], pid_t pid)
{
    int fd;
    int r_fd;
    int w_fd;

    printf("Parent: I'm going to close fd for Write\n");
	printf("Parent: I'm going to connect STDIN to fd for Read\n");
	printf("Parent: I'm going to connect STDOUT to fd from a file\n");
	printf("Parent: Eventually I'll read from STDIN (pipe) and write to STDOUT (file)\n");
    close(pipe[READ]);
    r_fd = dup2(pipe[WRITE], STDIN_FILENO); //표준입력을 pipe의 쓰는 것과 연결
    close(pipe[WRITE]);
    if (r_fd == -1)
        exit(1);
    fd = open("fork.out", O_WRONLY);
    if (fd == -1)
		exit(1);
    w_fd = dup2(fd, STDOUT_FILENO);
    close(fd);
    if (w_fd == -1)
		exit(1);
    if(waitpid(pid, NULL, 0) == -1)
        exit(1);
    parentcommand();
}

//이렇게 pipe()하면 두 개의 파일 설명자를 만드는 이유 가 명확해 집니다. 
// 작성자는 필요한 모든 데이터를 write fd에 쓰고 fd를 닫습니다. 
// 이것은 또한 EOF전송을 트리거합니다 . 
// 판독기는 일반적으로 데이터 EOF가 끝을 만나 닫을 때까지 데이터를 계속 읽 습니다. 
// 이 시나리오에서는 쓰기 fd가 닫혀 있지만 데이터가 여전히 파이프에 버퍼링되어 판독기에서 읽기를 기다리는 시간이 있습니다. 
// 단일 fd를 갖는 것은 이치에 맞지 않습니다. 작성자와 독자 프로세스 사이에 또 ​​다른 조정 계층이 필요하기 때문입니다. 
// 그렇지 않으면 누가 언제 마감을 할 것입니까?

// fd[1]은 쓰기용 WRITE
// fd[0]은 읽기용 READ


int main()
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
        return(1);
    printf("parent : fd for read is %d, fd for write is %d\n", fd[READ], fd[WRITE]);
    pid = fork();
    if(pid == -1) //fork 오류시
    {
        close(fd[READ]);
        close(fd[WRITE]);
        return (1);
    }
    else if (!pid)
        childproc(fd);
    else
        parentproc(fd, pid);
    return (0);
}

