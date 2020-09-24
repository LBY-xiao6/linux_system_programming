#include "common.h"

int main()
{
//    int fd = open("a.txt", O_RDWR);

//    // 功能: 复制0号描述符为fd
//    // 即从此之后，fd对应的文件与0一样
//    dup2(0, fd);

//    char buf[50];
//    bzero(buf, 50);
//    read(fd, buf, 50);

//    printf("%s", buf);


//    // 功能: 赋值fd号描述符为0
//    // 即从此之后，0对应的文件就跟fd一样
//    dup2(fd, 0);

//    // 从0号描述符对应的文件读取一个整数
//    int n;
//    scanf("%d", &n);

//    printf("n: %d\n", n);

    int fd = open("b.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);

    // 功能: 将1覆盖fd，fd丧失了原来的文件关联，fd就变成跟1一样
    dup2(1, fd);
    write(fd, "abc", 3); // 向屏幕输出abc

//    // 功能: 将fd覆盖1,1就丧失了原来的文件关联，1就变成跟fd一样
//    dup2(fd, 1);
//    printf("hello world!\n");




    return 0;
}
