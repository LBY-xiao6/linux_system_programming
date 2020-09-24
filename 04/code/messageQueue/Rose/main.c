#include "common.h"

int main()
{
    // 0，搞一个key
    key_t key = ftok(PROJ_PATH, PROJ_ID);

    // 1，创建/打开一个消息队列
    // IPC_CREAT: 如果不存在就创建，如果存在就打开
    int id = msgget(key, IPC_CREAT | 0666);
    if(id == -1)
    {
        perror("创建/打开消息队列失败");
        exit(0);
    }

    // 2，准备消息结构体来接收Jack的消息
    struct msgbuf buf;
    bzero(&buf, sizeof(buf));

    // 3，接收对方的消息并打印
    int n = msgrcv(id, &buf, 30, J2R, 0/*阻塞型接收*/);
    if(n == -1)
    {
        perror("接收消息失败");
        exit(0);
    }
    else
        printf("Jack的消息: %s", buf.data);

    // 4，收完消息后，删除消息队列
    msgctl(id, IPC_RMID, NULL);

    return 0;
}
