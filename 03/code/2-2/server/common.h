#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <syslog.h>

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

int daemon_init(void);
void mylog(const char *usrmsg, const char *errmsg);

#endif
