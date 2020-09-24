#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <errno.h>
#include <pthread.h>

#define MAX_WAITING_TASKS	1000
#define MAX_ACTIVE_THREADS	20

// 任务节点
struct task
{
	// 函数指针，指向线程要执行的任务
	void *(*do_task)(void *arg);

	// 任务的参数
	void *arg;

	// 单链表
	struct task *next;
};

// 线程池的管理结构体
typedef struct thread_pool
{
	// 互斥锁和条件量
	// 用来保证多线程的情况下，操作任务链表的秩序
	pthread_mutex_t lock;
	pthread_cond_t  cond;

	// 标示线程池是否关闭
	bool shutdown;

	// 任务链表
	struct task *task_list;

	// 所有线程的TID的存放点
	pthread_t *tids;

	// 一些辅助的数据
	unsigned max_waiting_tasks; // 最大等待任务数
	unsigned waiting_tasks;     // 当前等待任务数
	unsigned active_threads;    // 当前活跃线程数

}thread_pool;


// 线程池的接口声明
bool init_pool(thread_pool *pool, unsigned int threads_number);
bool add_task(thread_pool *pool, void *(*do_task)(void *arg), void *task);
int  add_thread(thread_pool *pool, unsigned int additional_threads_number);
int  remove_thread(thread_pool *pool, unsigned int removing_threads_number);
bool destroy_pool(thread_pool *pool);

void *routine(void *arg);


#endif
