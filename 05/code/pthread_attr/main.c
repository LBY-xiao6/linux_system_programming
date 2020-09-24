#include "common.h"
#include <errno.h>

void *routine(void *arg)
{
    // 将自己分离出去
    pthread_detach(pthread_self());

    pthread_exit("abcd");
}

int main()
{
    // 1，设置线程的属性变量
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // 2，根据属性变量来创建线程
    pthread_t tid;
    pthread_create(&tid, &attr, routine, NULL);

    void *val;
    int err = pthread_join(tid, &val);

    if(err == 0)
    {
        printf("子线程返回值: %s\n", (char *)val);
    }
    else
    {
        printf("获取子线程失败: %s\n", strerror(err));
    }

    return 0;
}
