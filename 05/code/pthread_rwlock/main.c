#include "common.h"

// 定义读写锁
pthread_rwlock_t rwlock;

// 全局共享的数据
// 大家都可以访问的数据，通常被称为临界资源
int global = 100;

void *routine1(void *arg)
{
    // 对临界资源发生操作的代码，称为临界代码

    // 由于以下代码对共享数据发生了读、写操作
    // 所以必须加写锁
    pthread_rwlock_wrlock(&rwlock);

    global += 1;
    printf("我是%s, global=%d\n", (char *)arg, global);
    sleep(1);

    // 离开了临界代码，必须解锁
    pthread_rwlock_unlock(&rwlock);

    pthread_exit(NULL);
}

void *routine2(void *arg)
{
    pthread_rwlock_wrlock(&rwlock);

    global = 666;
    sleep(1);
    printf("我是%s, global=%d\n", (char *)arg, global);

    pthread_rwlock_unlock(&rwlock);

    pthread_exit(NULL);
}

void *routine3(void *arg)
{
    pthread_rwlock_rdlock(&rwlock);

    if(global > 0)
        printf("我是%s，目前global>0\n");

    pthread_rwlock_unlock(&rwlock);

    pthread_exit(NULL);
}

int main()
{
    // 初始化读写锁
    pthread_rwlock_init(&rwlock, NULL);

    // 创建一些线程
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, routine1, "thread 1");
    pthread_create(&t2, NULL, routine2, "thread 2");
    pthread_create(&t3, NULL, routine3, "thread 3");

    // 主线程阻塞等待回收子线程，并销毁读写锁
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}
