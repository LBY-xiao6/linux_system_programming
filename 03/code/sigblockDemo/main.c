#include "common.h"

void f(int sig)
{
    printf("正在处理信号:%d... ...\n", sig);
}

int main()
{
    // 0，汇报自己的PID，方便别人给我发信号
    printf("我是:%d\n", getpid());

    // 1，关联信号XXX与响应函数
    signal(SIGINT, f);

    // 2，阻塞信号XXX
    // 2.1 将要阻塞的信号们放入信号集中
    sigset_t sigs;
    sigemptyset(&sigs);
    sigaddset(&sigs, SIGINT);

    // 2.2 将信号集交给sigprocmaks去集中处理
    sigset_t oldsigs;
    sigprocmask(SIG_BLOCK, &sigs, &oldsigs);

    // 3，休眠15秒钟
    for(int i=15; i>0; i--)
    {
        printf("%d\n", i);
        sleep(1);
    }

    // 4，解除信号XXX的阻塞
    sigprocmask(SIG_UNBLOCK, &sigs, &oldsigs);

    return 0;
}
