#include "common.h"

int main()
{
    pid_t pid = fork();

    if(pid > 0)
    {
        printf("PID:%d, PPID:%d\n", getpid(), getppid());

        // 判断子进程的退出值
        int status;
        wait(&status);

        switch (WEXITSTATUS(status))
        {
        case 0:
            printf("子进程成功执行了任务！\n");
            break;

        case 1:
            printf("子进程任务失败:xxx\n");
            break;

        case 2:
            printf("子进程任务失败:yyy\n");
            break;

        default:
            printf("子进程任务失败:不明原因\n");
            break;
        }

    }

    if(pid == 0)
    {
        // exec函数族
        // 功能: 让进程加载一段新的代码（旧瓶装新酒），覆盖原有的代码
        // 其中:
        //   "./childProcess" 是要加载的程序
        //   "./childProcess", "ab", "12", NULL 是程序的参数列表
#if 0
        printf("%d\n", __LINE__);
        execl("./childProcess", "./childProcess", "ab", "12", NULL);
        printf("%d\n", __LINE__);
#endif


#if 1
        // 没有获取环境变量PATH的值
        execl("/bin/ls", "/bin/ls", NULL);
#else
        // 从终端获取了环境变量PATH的值
        execlp("ls", "ls", NULL);
#endif
    }

    return 0;
}
