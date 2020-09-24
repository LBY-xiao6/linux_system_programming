#include "common.h"

// 余额
int balance = 0;

// 互斥锁与条件量
pthread_mutex_t m;
pthread_cond_t  v;

// 所有的子线程的启动函数
void *routine(void *args)
{
    // 加锁
    pthread_mutex_lock(&m);

    // 判断余额
    while(balance <= 0)
    {
        // 进入条件量v的等待房间
        // 进入以下函数，将自动解锁m
        // 退出以下函数，将自动加锁m
        pthread_cond_wait(&v, &m);
    }

    // 取钱
    balance -= 80;
    printf("我是第%d条线程，取了80元之后的余额是:%d\n", (int)args, balance);

    // 解锁
    pthread_mutex_unlock(&m);
}

int main(int argc, char **argv) // ./main 10
{
    // 初始化
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&v, NULL);

    // 创建一些子女线程
    pthread_t tid;
    for(int i=0; i<atoi(argv[1]); i++)
    {
        pthread_create(&tid, NULL, routine, (void *)i);
    }

    // 主线程充当了父母，去充钱
    pthread_mutex_lock(&m);
    balance += 500;
    pthread_mutex_unlock(&m);

    // 唤醒在条件量房间中睡觉的线程（们）
//    pthread_cond_signal(&v); // 唤醒一个
    pthread_cond_broadcast(&v); // 唤醒全部

    // 退出主线程
    pthread_exit(NULL);
}
