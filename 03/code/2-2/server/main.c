#include "common.h"

static bool begin = true;
static FILE *fp;

void saveData(const char *buf, int size)
{
    if(begin)
    {
        fp = fopen("/home/gec/mylog", "a+");
        begin = false;
    }

    // 将数据写入文件，并刷新缓冲区
    fwrite(buf, size, 1, fp);
    fflush(fp);
}

int main()
{
    // 1，变神仙
    daemon_init();


    // 2，创建管道，并打开管道
    mkfifo("/home/gec/fifo", 0666);
    int fd = open("/home/gec/fifo", O_RDWR);
    if(fd == -1)
    {
        mylog("打开管道失败", strerror(errno));
        exit(0);
    }


    // 3，不断地将管道数据读出并保存
    char buf[50];
    while(1)
    {
        bzero(buf, 50);
        int n = read(fd, buf, 50);

        if(n > 0)
        {
            saveData(buf, n);
        }
        else
        {
            mylog("读取管道数据失败", strerror(errno));
            exit(0);
        }
    }

    fclose(fp);
    close(fd);

    return 0;
}
