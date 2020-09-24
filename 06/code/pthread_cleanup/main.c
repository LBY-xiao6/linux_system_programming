#include "common.h"

// 搞一把互斥锁
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *count(void *arg)
{
    int i=1;
    while(1)
    {
        sleep(1);
        printf("计时: %d\n", i++);
    }
}

void handler(void *arg)
{
    printf("我[%u]被取消了！\n", (unsigned)pthread_self());
    pthread_mutex_unlock(&m);
}

void *routine(void *arg)
{
    // 写遗言
    // 如果将来我死了，请系统帮我执行以下handler
    pthread_cleanup_push(handler, NULL);

    // 加锁之后，如果本线程有可能在解锁之前被杀死（或被取消）
    // 那么就必须先写好遗言
    pthread_mutex_lock(&m);
    printf("[%u]已经锁上了muext!，开始干活...\n", (unsigned)pthread_self());

    // 干一些事情...
    sleep(2);
    printf("[%u]活干完了，准备收工\n", (unsigned)pthread_self());

    pthread_mutex_unlock(&m);
    printf("[%u]锁已经解了，下班走人\n", (unsigned)pthread_self());


    // 如果此刻我还没死，那么后面我再死去也不怕了
    // 为了节省系统资源，要将刚刚写好的遗言清除
    // 0: 意味着清除遗言函数，并且不执行
    pthread_cleanup_pop(0);

    pthread_exit(NULL);
}


int main()
{
    // 计时
    pthread_t t;
    pthread_create(&t, NULL, count, NULL);

    // 创建线程，观察死锁
    pthread_t t1, t2;
    pthread_create(&t1, NULL, routine, NULL);
    pthread_create(&t2, NULL, routine, NULL);
    printf("[%u] ==> t1\n", (unsigned)t1);
    printf("[%u] ==> t2\n", (unsigned)t2);
    printf("[%u] ==> main\n", (unsigned)pthread_self());

    sleep(1);
    pthread_cancel(t1);
    pthread_cancel(t2);

    pthread_mutex_lock(&m);
    printf("主线程加到了锁\n");
    pthread_mutex_unlock(&m);
    printf("主线程解了锁\n");

    pthread_exit(NULL);
}
