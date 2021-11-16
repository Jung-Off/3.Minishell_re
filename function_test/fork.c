#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global; //전역변수 데이터 영역

int main(void)
{
    int automatic; //스택영역
    int *heap;      //힙영역
    pid_t pid;

    global = 10;
    automatic = 10;
    heap = (int *)malloc(sizeof(int));

    if(!heap)
    return (1);

    *heap = 10;
    pid = fork();
    if (pid == -1)
    {
        free(heap);
        return (1);
    }
    else if(!pid) //자식
    {
       printf("Child: Before operations -> %d (Global), %d (Automatic), %d (Heap)\n", global, automatic, *heap);
		global += 10;
		automatic += 10;
		*heap += 10;
		printf("Child: After operations -> %d (Global), %d (Automatic), %d (Heap)\n", global, automatic, *heap);
    }
    else if (pid) //부모
	{
		printf("Parent: Before operations -> %d (Global), %d (Automatic), %d (Heap)\n", global, automatic, *heap);
		global += 20;
		automatic += 20;
		*heap += 20;
		printf("Parent: After operations -> %d (Global), %d (Automatic), %d (Heap)\n", global, automatic, *heap);
	}
	free(heap);
	return (0);
}

//자식 프로세스와 부모 프로세스의 메모리 공간이 별도로 구성된다는 것은 위와 같은 코드를 실행함으로써 쉽게 알 수 있다.
//메모리 공간이 별도이므로 자식 프로세스에서의 증감 연산 결과와 부모 프로세스에서의 증감 연산의  