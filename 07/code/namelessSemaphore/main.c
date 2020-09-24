#include "common.h"

// 定义POSIX无名信号量
sem_t s;

void *routine(void *arg)
{
    char *t = (char *)arg;
    if(strcmp(t, "t1")==0)
    {
        while(1)
        {
            // 进行P操作
            sem_wait(&s);

            // 疯狂输出字母
            for(int i=0; i<26; i++)
            {
                fprintf(stderr, "%c", 'a'+i);
                usleep(20*1000);
            }

            // 进程V操作
            sem_post(&s);
        }
    }

    if(strcmp(t, "t2")==0)
    {
        while(1)
        {
            // 进行P操作
            sem_wait(&s);

            // 疯狂输出数字
            for(int i=0; i<10; i++)
            {
                fprintf(stderr, "%d", i);
                usleep(20*1000);
            }

            // 进程V操作
            sem_post(&s);
        }
    }
}

int main()
{
    // 1，初始化
    sem_init(&s, 0/*作用范围是线程间*/, 1/*初始值*/);

    // 2，搞两条线程去进程P/V操作
    pthread_t t1, t2;
    pthread_create(&t1, NULL, routine, "t1");
    pthread_create(&t1, NULL, routine, "t2");


    pthread_exit(NULL);
}
