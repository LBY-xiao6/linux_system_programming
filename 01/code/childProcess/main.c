#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    // 输出所有的外部参数
    for(int i=0; i<argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    printf("我是子进程: PID=[%d], PPID=[%d]\n",
           getpid(), getppid());

    // 关于退出值的约定
    // 成功: 0
    // 失败: 非零
    return 1;
}
