#include "common.h"

int main()
{
    pid_t pid = fork();

    if(pid > 0)
    {
        // 等待子进程的退出
        // 1，阻塞等待子进程
        // 2，可以获取子进程的退出状态
        // 3，释放子进程的资源，让其脱离僵尸状态
        int status;
        wait(&status); // 将子进程的退出状态，装到status中

        // status是子进程的退出状态，从中可以获得
        // 1，子进程的退出值
        // 2，子进程的退出模式（比如正常退出、异常退出）
        // 3，杀死子进程的信号
        // .. ..
        printf("子进程的退出值:%d\n", WEXITSTATUS(status));

        // 然后再执行下面的语句
        printf("父进程\n");

        // 退出当前进程
        exit(0);
    }
    else
    {
        printf("子进程\n");

        // 退出当前进程
        exit(88);

        // 本进程退出之后，所占据的内存资源不会立即释放
        // 直到本进程的父进程来释放我的资源为止
        // 在此期间，本进程被称为 “僵尸进程” (Zombie)
    }
}
