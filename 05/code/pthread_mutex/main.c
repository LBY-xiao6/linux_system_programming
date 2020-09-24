#include "common.h"

// 定义互斥锁
pthread_mutex_t m;

void output(const char *s)
{
    while(*s != '\0')
    {
        putc(*s, stderr);
        usleep(1000);
        s += 1;
    }
    return;
}

void *routine(void *arg)
{
    pthread_mutex_lock(&m);
    output("info output bu sub-thread.\n");
    pthread_mutex_unlock(&m);
}

int main()
{
    // 初始化互斥锁
    pthread_mutex_init(&m, NULL);

    pthread_t tid;
    pthread_create(&tid, NULL, routine, NULL);

    pthread_mutex_lock(&m);
    output("message delivered by main thread.\n");
    pthread_mutex_unlock(&m);

    // 在main函数中return，相当于退出了进程，即所有的线程都被迫退出了
    // return 0;

    // 退出当前线程
    pthread_exit(NULL);
}
