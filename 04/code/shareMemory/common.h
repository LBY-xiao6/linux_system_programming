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

#define PROJ_PATH "/mnt/hgfs/codes/04/code/sharedMemory"
#define PROJ_ID   1

#endif
