#include "common.h"

int main(void)
{
	// 1，创建有名管道
	mkfifo("/home/gec/fifo", 0666);

	// 2，打开管道
	int fd = open("/home/gec/fifo", O_RDWR);
	if(fd == -1)
	{
		perror("打开管道失败");
		exit(0);
	}


	// 3，向对方说一句话
	write(fd, "abcd", 4);

	close(fd);
	return 0;
}
