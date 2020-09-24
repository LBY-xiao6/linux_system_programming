#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#include <linux/fb.h>
#include <linux/input.h>

#include <string.h>
#include <errno.h>
#include <time.h>
#include <wait.h>
#include <fcntl.h>

#include <dirent.h>

#include <sys/ipc.h>
#include <sys/msg.h>

#define PROJ_PATH "/mnt/hgfs/codes/04/code/messageQueue"
#define PROJ_ID   1


// 消息结构体
struct msgbuf
{
	// 第一个成员是规定long型，是每个消息的标签
	long type;

	// 后续成员没有规定，想发什么数据就写什么
	char data[30];

};

// 自定义消息标签
#define J2R 1
#define R2J 2


#endif
