#include "common.h"

int f(int sig)
{
    printf("收到信号: %d\n", sig);
}

int main()
{
    // 关联指定的信号与函数
    signal(SIGHUP, f); // 1号信号
    signal(SIGINT, f); // 2号信号

    // 忽略指定的信号
    signal(SIGQUIT, SIG_IGN); // 3号信号
    signal(SIGILL,  SIG_IGN); // 4号信号


    // 静静地等待信号的到来.. ..
    // 将pause放入循环中，可不断地接收信号
    while(1)
    {
        pause();
    }

    return 0;
}
