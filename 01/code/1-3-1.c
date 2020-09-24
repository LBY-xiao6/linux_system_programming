#include "common.h"

int main(void)
{
	for(int i=0; i<10; i++)
	{
		// 打印PID
		printf("PID:%d, PPID:%d\n", getpid(), getppid());

		pid_t pid = fork();

		if(pid > 0) // parent
		{
			break;
		}

		if(pid == 0) // child
		{
			continue;
		}
	}

	exit(0);
}
