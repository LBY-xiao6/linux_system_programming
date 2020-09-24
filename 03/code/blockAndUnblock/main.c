#include "common.h"

int main()
{
    int fd[2];
    pipe(fd);


    char buf[10];
    bzero(buf, 10);

    // 将管道设置为非阻塞状态
    // a.获取当前文件的flags
    int flags = fcntl(fd[0], F_GETFL);

    // b.在flags的基础上，设置非阻塞属性
    flags |= O_NONBLOCK;

    // c.将新的flags设置为文件的FL
    fcntl(fd[0], F_SETFL, flags);

    // 此处，管道是非阻塞的
    int n = read(fd[0], buf, 10);
    if(n > 0)
        printf("读取到数据: %s", buf);
    if(n == 0)
        printf("管道无写者，且无数据\n");
    if(n < 0)
        perror("读取管道失败");


    // 重新将管道设置为阻塞状态
    flags = fcntl(fd[0], F_GETFL);
    flags &= ~O_NONBLOCK;
    fcntl(fd[0], F_SETFL, flags);

    printf("试图读取管道内容...\n");
    n = read(fd[0], buf, 10);
    if(n > 0)
        printf("读取到数据: %s", buf);
    if(n == 0)
        printf("管道无写者，且无数据\n");
    if(n < 0)
        perror("读取管道失败");

    return 0;
}
