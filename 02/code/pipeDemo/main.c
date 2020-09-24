#include "common.h"

int main()
{
    // 创建无名管道
    int fd[2];
    pipe(fd);

    // 创建子进程
    pid_t pid = fork();

    // parent
    if(pid > 0)
    {
        // 父进程只负责读取管道数据，所以最好关闭写端
        close(fd[1]);

        char buf[20];
        // 静静地等待子进程的消息...
        bzero(buf, 20);
        read(fd[0], buf, 20);
        printf("第一次收到子进程的消息:%s\n", buf);

        // 静静地等待子进程的消息...
        bzero(buf, 20);
        read(fd[0], buf, 20);
        printf("第二次收到子进程的消息:%s\n", buf);
    }

    // child
    if(pid == 0)
    {
        // 子进程只负责将数据写入管道，所以最好关闭读端
        close(fd[0]);

        sleep(2);
        write(fd[1], "你好", 20);

        // 暂停
//        pause();
    }

    return 0;
}
