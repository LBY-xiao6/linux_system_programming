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

    // 3，将数据写入共享内存
    printf("按回车给共享内存写入数据\n");
    getchar();
    snprintf(addr, 1024, "%s", "You jump, I jump!\n");

    // 4，解除共享内存的映射
    shmdt(addr);

    return 0;
}
