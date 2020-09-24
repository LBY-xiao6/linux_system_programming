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
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>

#define PROJ_PATH "/home/gec/"
#define PROJ_SHM  1
#define PROJ_SEM  2

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

#endif
