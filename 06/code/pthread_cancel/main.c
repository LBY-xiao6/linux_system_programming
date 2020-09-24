#include "common.h"

void *routine(void *avg)
{
    // 关闭取消状态，即不可被取消
    // NULL: 代表不保留原来的状态
//    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

    // 将取消类型，设置为不延迟
    // NULL: 代表不保留原来的类型
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    // 拖时间
    unsigned long long i, j;
    long double f1, f2;
    for(i=0; i<10000; i++)
    {
        for(j=0; j<80000; j++)
        {
            f1 = f2;
        }
    }

    // 循环输出'x';
    while(1)
    {
        // 以下函数是取消点，意味着本线程收到取消要求之后，
        // 在执行完取消点函数之后，就退出。
        fprintf(stderr, "%c", 'x');
    }
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, routine, NULL);

    // 取消tid这条线程
    pthread_cancel(tid);

    int ret = pthread_join(tid, NULL);
    if(ret == 0)
        printf("回收成功！\n");
    else
        printf("回收失败！\n");

    pthread_exit(NULL);
}
