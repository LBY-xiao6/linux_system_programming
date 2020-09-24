#include "common.h"

int main()
{
    // 0，创建一个专属的key
    key_t key = ftok(PROJ_PATH, PROJ_ID);

    // 1，创建/打开共享内存
    int id = shmget(key, 1024, IPC_CREAT|0666);

    // 2，将共享内存映射到本进程内存空间
    // id: 你要映射的共享内存
    // NULL: 代表让系统帮你决定映射之后的入口地址
    // 0: 代表映射后对共享内存可读可写
    char *addr = shmat(id, NULL, 0);

    // 3，将数据从共享内存中读出
    printf("按回车将共享内存中的数据打印出来\n");
    getchar();
    printf("%s", addr);

    // 4，解除共享内存的映射
    shmdt(addr);

    // 5，删除共享内存对象
    shmctl(id, IPC_RMID, NULL);

    return 0;
}
