#include <stdio.h>
#include <unistd.h>
/* 자식 프로세스를 생성한다. */
int main(){
    int pid, a=1, b=2, sum;

    printf("[%d] 프로세스 시작 \n", getpid());
    pid = fork();
    printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);
    printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);    
    printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);
    sum = a+b;
    printf("[%d] sum : %d\n", getpid(), sum);
}
