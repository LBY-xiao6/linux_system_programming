#include "common.h"

int main(void)
{
	for(int i=0; i<10; i++)
	{
		pid_t pid = fork();

		if(pid > 0) // parent
		{
			// 等待子进程
			wait(NULL);

			// 打印PID
			printf("PID:%d, PPID:%d\n", getpid(), getppid());
			exit(0);
		}

		if(pid == 0) // child
		{
			continue;
		}
	}

}

















