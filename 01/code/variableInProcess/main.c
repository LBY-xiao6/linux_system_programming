#include "common.h"

// 数据段
int global = 100;

int main()
{
    // 栈
    int x = 200;

    // 堆
    int *p = malloc(sizeof(int));
    *p = 300;

    // 文件IO缓冲区
    printf("缓冲区中的数据\n");


    pid_t pid = fork();
    if(pid > 0)
    {
        // 查看内存中各个区域的数据是否受到影响
        printf("global:%d\n", global);
        printf("x:%d\n", x);
        printf("*p:%d\n", *p);
    }
    else if(pid == 0)
    {
        // 修改内存中的各个变量
        global = 666;
        x = 777;
        *p = 888;
    }
    else
    {
        perror("创建子进程失败");
        exit(0);
    }

    return 0;
}
