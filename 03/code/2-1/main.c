#include "common.h"

int main()
{
    // 1，创建无名管道
    int fd[2];
    pipe(fd);

    // 2，创建子进程
    pid_t pid = fork();

    // 父进程
    if(pid > 0)
    {
        // 将标准输出（1号描述符）重新定向到管道的写端
        dup2(fd[1], STDOUT_FILENO); // cp file1 file2

        // 此时，执行ls，他将会把数据写入1号描述符，即管道的写端
        execlp("ls", "ls", NULL);
    }

    // 子进程
    if(pid == 0)
    {
        // 将标准输入（0号描述符）重新定向到管道的读端
        dup2(fd[0], STDIN_FILENO); // cp file1 file2

        close(fd[1]);

        // 此时，执行wc，他将会从0号描述符读取数据，即管道的读端
        execlp("wc", "wc", "-w", NULL);
    }

    return 0;
}
