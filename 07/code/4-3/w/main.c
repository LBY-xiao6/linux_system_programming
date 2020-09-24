#include "common.h"

// writer: 写者

int main()
{
    // 1，打开或者创建有名信号量
    sem_t *s1 = sem_open("/memory", O_CREAT, 0666, 1);
    sem_t *s2 = sem_open("/data",   O_CREAT, 0666, 0);

    // 2，准备好共享内存
    int id  = shmget(ftok("/home/gec", 1), 1024, IPC_CREAT|0666);
    char *p = shmat(id, NULL, 0);

    // 3，不断向共享内存写入数据
    while(1)
    {
        // a.申请内存资源
        sem_wait(s1);

        bzero(p, 1024);
        fgets(p, 1024, stdin);

        // b.增加数据资源
        sem_post(s2);
    }

    return 0;
}
