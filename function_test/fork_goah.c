#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//getppid 부모 프로세스 id 리턴
//getpid 함수를 호출한 프로세스 id 리턴 

int main(){
        int pid;
        int status;
        int terminate;
    
        if((pid=fork())==0){
                sleep(1);
                printf("\t [child process %d] created from %d\n",
                        getpid(), getppid());
                //  자기 (부모의 pid), 이건 부모가 나와야 되는거 아님? (부모의 getpid값)
                exit(0);
        }
        printf("[parent process %d] create %d process, ppid:%d\n",
                        getpid(),pid,getppid());
                        //부모 프로세스 자기 pid , 자식 process id, 부모 ?
    //+add 수정
    terminate = wait(&status);
    printf("[parent process ] process wait process %d, status %d\n", terminate, status);
}

