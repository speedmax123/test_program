#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void
printids(const char * s) {
	pid_t 		pid;
	pthread_t 	tid;
	
	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n",
										s,
										(unsigned int)pid,
										(unsigned int)tid,
										(unsigned int)tid);
}

void *
thr_fn(void * arg) {
	printids("new thread: ");
	return ((void *)0);
}

int
main(void) {
	int 	err;
	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if(err != 0) {
		err_quit("can not create thread: %s\n", strerror(err));
	}
	printids("main thread: ");
	//if the main thread does not sleep for a while and quit imediately,
	//the new created child thread may not have a chance to execute
	sleep(1);
	exit(0);
}
