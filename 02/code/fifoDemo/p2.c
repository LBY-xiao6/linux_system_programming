#include "common.h"

int main(void)
{
	// 1，创建有名管道
	mkfifo("/home/gec/fifo", 0666);

	// 2，打开管道
	int fd = open("/home/gec/fifo", O_RDONLY);
	if(fd == -1)
	{
		perror("打开管道失败");
		exit(0);
	}


	// 3，等待对方的消息
	char buf[10];
	bzero(buf, 10);
	read(fd, buf, 10);

	printf("对方的消息: %s", buf);

	close(fd);
	return 0;
}
