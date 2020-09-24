#include "common.h"

// f是信号响应函数，注意接口是固定的
void f(int sig)
{
    // 回收了一个僵尸子进程
    int status;
    wait(&status);
    printf("%d号子进程已被回收\n", WEXITSTATUS(status));
}

int main()
{
    // 关联信号与函数
    // 即: 将来如果我收到 SIGCHLD，就去执行f
    signal(SIGCHLD, f);

    int n = 0;
    while(1)
    {
        n++;
        pid_t pid = fork();

        // 父进程，1秒生一个孩子
        if(pid > 0)
        {
            pause();
            sleep(1);
            continue;
        }

        // 子进程，生出来就死掉
        if(pid == 0)
        {
            exit(n);
        }
    }

    return 0;
}
