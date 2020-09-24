#include "common.h"

// 信号的响应处理函数，函数头（接口）是系统规定的
void cleanup(int sig)
{
    // 回收僵尸子进程
    wait(NULL);

    // 使用非阻塞版本来回收僵尸子进程
    // -1: 查看任意子进程死了没有
    // NULL: 对子进程怎么死（退出状态）的不感兴趣
    // WNOHANG: 非阻塞回收（如果死了就立刻释放其资源，如果没死拉倒，我就走了）
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main()
{
    // 关联子进程终止的信号及其处理函数
    signal(SIGCHLD, cleanup);

    while(1)
    {
        pid_t pid = fork();

        // 父进程
        if(pid > 0)
        {
            sleep(1);
            continue;
        }


        // 子进程
        if(pid == 0)
        {
            // 1，打开预谋好的管道
            int fd = open("/home/gec/fifo", O_WRONLY);
            if(fd == -1)
            {
                perror("服务器未启动或管道文件打开失败");
                exit(0);
            }

            // 2，将系统时间、自身PID放入buf中
            char buf[50];
            bzero(buf, 50);
            time_t t = time(&t);
            snprintf(buf, 50, "PID:%d 时间:%s",
                     getpid(), ctime(&t));

            // 3，将buf中的数据写入管道
            write(fd, buf, strlen(buf));

            printf("%s", buf);
            break;
        }
    }

    return 0;
}
