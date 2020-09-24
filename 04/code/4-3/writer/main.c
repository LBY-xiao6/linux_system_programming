#include "common.h"

// 对信号量semid中的第n个元素，进行P操作
void sem_p(int semid, int n)
{
    struct sembuf buf;
    bzero(&buf, sizeof(buf));

    buf.sem_num = n; // 第n个元素
    buf.sem_op  = -1;// 减操作
    buf.sem_flg = 0; // 默认的选项

    // 此处就是P操作，申请资源，可能会发生阻塞
    semop(semid, &buf, 1);
}

// 对信号量semid中的第n个元素，进行V操作
void sem_v(int semid, int n)
{
    struct sembuf buf;
    bzero(&buf, sizeof(buf));

    buf.sem_num = n; // 第n个元素
    buf.sem_op  = +1;// 加操作
    buf.sem_flg = 0; // 默认的选项

    // 此处就是V操作，增加资源，永不阻塞
    semop(semid, &buf, 1);
}

int main()
{
    // 0，创建两个key
    key_t key1 = ftok(PROJ_PATH, PROJ_SHM);
    key_t key2 = ftok(PROJ_PATH, PROJ_SEM);


    // 1，创建共享内存、信号量
    int shmid = shmget(key1, 256, IPC_CREAT|0666);
    int semid = semget(key2, 2, IPC_CREAT|0666);

    // 2，映射共享内存
    char *addr = shmat(shmid, NULL, 0);

    // 3，初始化信号量
    union semun a;

    // 将第0个信号量元素的值，设置为a.val
    a.val = 1;
    semctl(semid, 0, SETVAL, a);

    // 将第1个信号量元素的值，设置为a.val
    a.val = 0;
    semctl(semid, 1, SETVAL, a);

    // 4，不断往共享内存中写入数据
    while(1)
    {
        // 对代表内存的第0个信号量元素进行P操作
        sem_p(semid, 0);

        // 直接往共享内存输入数据
        fgets(addr, 256, stdin);

        // 对代表数据的第1个信号量元素进程V操作
        sem_v(semid, 1);
    }

    return 0;
}
