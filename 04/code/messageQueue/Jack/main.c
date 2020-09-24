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

    // 2，准备消息结构体
    struct msgbuf buf;
    bzero(&buf, sizeof(buf));
    buf.type = J2R;

    // 3，输入数据并发送
    fgets(buf.data, 30, stdin);
    msgsnd(id, &buf, strlen(buf.data)+1, 0/*阻塞型发送*/);


    return 0;
}
