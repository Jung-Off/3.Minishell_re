#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
int main(){
 
        if(fork()==0){
                printf("\t child process created and exit\n");
                exit(0);
        }
        printf("parent process sleep\n");
        sleep(10);
        sleep(10);
        printf("process exit\n");
}

