#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>

void *routine(void *arg)
{
	if(*(char *)arg == 'A')
		nice(0);
	else if(*(char *)arg == 'B')
		nice(0);

	while(1)
	{
		fprintf(stderr, "%c", *(char *)arg);
	}
}

int main(int argc, char **argv)
{
	pthread_attr_t attr1;
	pthread_attr_t attr2;

	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);

	pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

	pthread_attr_setschedpolicy(&attr1, SCHED_RR);
	pthread_attr_setschedpolicy(&attr2, SCHED_RR);

	struct sched_param param1;
	struct sched_param param2;
	param1.sched_priority = 91;
	param2.sched_priority = 92;
	pthread_attr_setschedparam(&attr1, &param1);
	pthread_attr_setschedparam(&attr2, &param2);

	pthread_t tid1, tid2;
	pthread_create(&tid1, &attr1, routine, "A");
	pthread_create(&tid2, &attr2, routine, "B");

	pause();
	return 0;
}
