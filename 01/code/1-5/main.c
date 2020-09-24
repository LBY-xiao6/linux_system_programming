#include "common.h"

int main()
{
    int count = 0;
    while(1)
    {
        pid_t pid = fork();

        // 父进程循环生孩子
        if(pid > 0)
        {
            printf("已经产生了%d个僵尸\n", ++count);
            continue;
        }

        // 子进程直接跳出并退出变僵尸
        else if(pid == 0)
            break;

        // 出错了
        else
        {
            perror("复刻子进程失败");
            break;
        }
    }

    return 0;
}
