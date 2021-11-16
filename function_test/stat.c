




#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    printf("====stat test====\n");
    struct stat buf_s;
    struct stat buf_s2;
    int ret_s = stat("/Users/jji/3.Minishell_re", &buf_s);
    int ret_s2 = stat("/Users/jji/3.Mini", &buf_s2);

    printf("success_path : %d\n", ret_s);
    printf("fail_path : %d\n", ret_s2);
    printf("File size: %lld bytes\n", (long long) buf_s.st_size);
    printf("File size: %lld bytes\n", (long long) buf_s2.st_size);



    printf("\n=====stat test symbolic link=====\n");
    struct stat buf_s3;
    struct stat buf_s4;
    int ret_s3 = stat("/Users/jji/3.Minishell_re/new", &buf_s3);
    int ret_s4 = stat("/Users/jji/3.Minishell_re/link", &buf_s4);
    //link에 연결된 new의 크기

    printf("success_path : %d\n", ret_s3);
    printf("success_path : %d\n", ret_s4);
    printf("File size: %lld bytes\n", (long long) buf_s3.st_size);
    printf("File size: %lld bytes\n", (long long) buf_s4.st_size);


    printf("\n=====lstat test symbolic link=====\n");
    struct stat buf_s5;
    struct stat buf_s6;
    int ret_s5 = lstat("/Users/jji/3.Minishell_re/new", &buf_s5);
    int ret_s6 = lstat("/Users/jji/3.Minishell_re/link", &buf_s6);

    
    printf("success_path : %d\n", ret_s5);
    printf("success_path : %d\n", ret_s6);
    printf("File size: %lld bytes\n", (long long) buf_s5.st_size);
    printf("File size: %lld bytes\n", (long long) buf_s6.st_size);
    //link에 연결된 new의 크기!
    //link자체의 크기!

    return 0;
}
