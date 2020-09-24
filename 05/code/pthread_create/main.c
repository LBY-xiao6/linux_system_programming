#include "common.h"
#include <pthread.h>

// 线程的启动函数
void *routine(void *arg)
{
    int a = *(int *)arg;
    printf("a: %d\n", a);

    // 打印一些数字
    for(int i=0; i<10; i++)
    {
        a++;
        fprintf(stderr, "%d", a);
        usleep(200*1000);
    }

    // 退出线程
    pthread_exit("abcdefg");

    // 线程一旦退出，立即就会变成僵尸线程
}

int main()
{
    // 创建一条线程
    // 如果创建成功，系统会为这条线程分配一个ID号称为线程ID
    // tid: 存放线程ID
    // NULL: 不指定特定的线程属性，创建一条标准线程
    // routine: 线程的启动函数
    // &a: 传给线程的参数
    pthread_t tid;
    int a = 100;
    pthread_create(&tid, NULL, routine, (void *)&a);

    // 主线程
    // 打印一些字母
//    for(int i=0; i<10; i++)
//    {
//        i %= 26;
//        fprintf(stderr, "%c", 'A'+i);
//        usleep(200*1000);
//    }

    // 静静地等待回收子线程的资源... ...
    void *val;
    pthread_join(tid, &val); // 相当于wait()/waitpid()
    printf("返回值: %s\n", (char *)val);

    return 0;
}
