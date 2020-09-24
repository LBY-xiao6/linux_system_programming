#include "common.h"

int main()
{
    for(int i=0; i<10; i++)
    {
        pid_t pid = fork();

        if(pid > 0) // 父进程
        {
            continue;
        }

        if(pid == 0) // 子进程
        {
            printf("PID: %d, PPID: %d\n", getpid(), getppid());
            exit(0);
        }
    }

    // 父进程要等待并回收所有子进程
    for(int i=0; i<10; i++)
        wait(NULL);

    // 然后再打印PID
    printf("PID: %d, PPID: %d\n", getpid(), getppid());


    return 0;
}
