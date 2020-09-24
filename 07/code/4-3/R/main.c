#include "common.h"

// reader: 读者

int main()
{
    // 1，打开或者创建有名信号量
    sem_t *s1 = sem_open("/memory", O_CREAT, 0666, 1);
    sem_t *s2 = sem_open("/data",   O_CREAT, 0666, 0);

    // 2，准备好共享内存
    int id  = shmget(ftok("/home/gec", 1), 1024, IPC_CREAT|0666);
    char *p = shmat(id, NULL, 0);

    // 3，不断从共享内存读出数据
    while(1)
    {
        // a.申请数据资源
        sem_wait(s2);

        printf("对方发来数据:%s", p);

        // b.增加内存资源
        sem_post(s1);
    }

}
