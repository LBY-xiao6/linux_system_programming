#include "common.h"

int main()
{
    // 1，创建POSIX有名信号量
    sem_t *s = sem_open("/abc", O_CREAT, 0666, 1/*初始值*/);
    if(s == SEM_FAILED)
        perror("创建有名信号量失败");
    else
        printf("创建有名信号量成功");

    // 2，创建两个进程，使之使用以上信号量来进行协同
    pid_t p1, p2;
    p1 = fork();
    if(p1 > 0)
    {
        p2 = fork();
        if(p2 > 0)
            exit(0);

        // 进程p2:
        else
        {
            while(1)
            {
                // 进行P操作
                sem_wait(s);

                // 疯狂输出字母
                for(int i=0; i<26; i++)
                {
                    fprintf(stderr, "%c", 'a'+i);
                    usleep(20*1000);
                }

                // 进程V操作
                sem_post(s);
            }
        }
    }

    // 进程p1:
    else
    {
        while(1)
        {
            // 进行P操作
            sem_wait(s);

            // 疯狂输出数字
            for(int i=0; i<10; i++)
            {
                fprintf(stderr, "%d", i);
                usleep(20*1000);
            }

            // 进程V操作
            sem_post(s);
        }
    }

    return 0;
}
