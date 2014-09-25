#include "apue.h"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

extern int makethread(void *(*fn)(void *), void * arg);

struct to_info {
	void (*to_fn)(void *);		/* function */
	void *to_arg;				/* arg		*/
	struct timespec to_wait;	/* time to wait */
};

#define SECTONSEC 	1000000000	/* seconds to nanoseconds */
#define USECTONSEC	1000		/* mircoseconds to nanoseconds */

void *
timeout_helper(void *arg) {
	struct to_info *tip;
	tip = (struct to_info *)arg;
	nanosleep(&tip->to_wait, NULL);
	(*tip -> to_fn)(tip -> to_arg);
	return(0);
}

void
timeout(const struct timespec *when, void (*func)(void *), void *arg) {
	struct timespec 	now;
	struct timeval 		tv;
	struct to_info * 	tip;
	int					err;

	gettimeofday(&tv, NULL);
	now.tv_sec = tv.tv_sec;
	now.tv_nsec = tv.tv_usec * USECTONSEC;
	
	if ((when -> tv_sec > now.tv_sec) ||
			(when -> tv_sec == now.tv_sec && when -> tv_nsec > now.tv_nsec )) {
		tip = (struct to_info *)malloc(sizeof(struct to_info));
		if (tip != NULL) {
			tip -> to_fn = func;
			tip -> to_arg = arg;
			tip -> to_wait.tv_nsec = when -> tv_sec - now.tv_sec;
			if (when -> tv_nsec >= now.tv_nsec) {
				tip -> to_wait.tv_nsec = when -> tv_nsec - now.tv_sec;
			}
			else {
				tip -> to_wait.tv_sec--;
				tip -> to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_sec;
			}
			/* init time ok */
			printf("init time ok\n");
			err = makethread(timeout_helper, (void *)tip);
			if (err == 0) {
				return;	
			}
		}
		/**
		 *	we get here if (a) when <= now or mallc error or we cannot make a thread, just call the function
		 */
		printf("byebye!\n");
		(*func)(arg);
	}
}

pthread_mutexattr_t attr;
pthread_mutex_t mutex;

void
retry(void *arg) {
	pthread_mutex_unlock(&mutex);
	/* perform retry steps */
	printf("we are trying to do something\n");
	pthread_mutex_lock(&mutex);
}

int
main(void) {
	//int				err, condition, arg;
	int				err,arg;
	struct timespec when;
	
	if ((err = pthread_mutexattr_init(&attr)) != 0) {
		err_exit(err, "pthread_mutex_init failed");
	}
	if ((err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) != 0) {
		err_exit(err, "can't set recursive type");
	}
	if ((err = pthread_mutexattr_init(&attr)) != 0) {
		err_exit(err, "can not create a recursive mutex");
	}
	pthread_mutex_lock(&mutex);
	printf("locked\n");
	if (1) {
		printf("timeout is going to be\n");
		timeout(&when, retry, (void *)arg);
	}
	pthread_mutex_unlock(&mutex);
	exit(0);
}
