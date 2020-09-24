#include "common.h" 

void mylog(const char *usrmsg, const char *errmsg)
{
    char buf[100];
    bzero(buf, 100);
    snprintf(buf, 100, "%s:%s\n", usrmsg, errmsg);

    syslog(LOG_DAEMON, buf);
}

int daemon_init(void)
{
	pid_t pid;
	int fd0, fd1, fd2, max_fd,i;	

	// 1
	if((pid = fork()) < 0)
	{
		perror("fork faild!");
		exit(1);
	}
    else if(pid > 0)
	{
		exit(0);
	}
    printf("第1步成功\n");

	// 2
	signal(SIGHUP, SIG_IGN);
    printf("第2步成功\n");

	// 3
	if(setsid() < 0)
	{
		exit(1);
	}
    printf("第3步成功\n");

	// 4
	if((pid = fork()) < 0)
	{
		perror("fork faild!");
		exit(1);
	}
    else if(pid > 0)
		exit(0);
    printf("第4步成功\n");

	// 5
	setpgrp();
    printf("第5步成功\n");

    // 6
    // 准备好写系统日志
    openlog("Server", LOG_CONS | LOG_PID, LOG_DAEMON);

    // 7
    // 首先获取进程所能打开的文件描述符的最大值
	max_fd = sysconf(_SC_OPEN_MAX);
    // 将所有的文件描述符全部关闭（包括标准输入、输出）
	for (i = max_fd; i>=0; i--)
	{
        close(i);
	}

	// 7
	umask(0);

	// 8
	chdir("/");


	return 0;
}
