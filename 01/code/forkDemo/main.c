#include "common.h"

int main()
{
    printf("%d\n", __LINE__);

    // 将本进程复刻一个子进程
    // 1，fork函数将本进程复制一份，并使之成为独立的子进程
    // 2，子进程拥有父进程拷贝过来的一切代码，但只从fork函数往下开始执行
    // 3，父子进程同时并发运行，此刻无法确定他们的执行次序.
    // 4，fork函数在父子进程两处，分别返回不同的值（大于0是父进程，等于0是子进程）
    pid_t pid = fork();

    // 子进程
    if(pid == 0)
        printf("[%d]我是子进程，我的身份证号码PID:%d\n", __LINE__, getpid());

    // 父进程
    if(pid > 0)
        printf("[%d]我是父进程，我的身份证号码PID:%d\n", __LINE__, getpid());

    return 0;
}
