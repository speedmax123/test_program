#include "apue.h"
#include <pthread.h>
#include <string.h>

struct foo {
	int a, b, c, d;
};

void
printfoo(const char * s, const struct foo * fp) {
	
	printf("%s",s);
	printf("	structure at 0X%x\n", (unsigned)fp);
	printf("	foo.a = %d\n", fp -> a);
	printf("	foo.b = %d\n", fp -> b);
	printf("	foo.c = %d\n", fp -> c);
	printf(" 	foo.d = %d\n", fp -> d);
}

void *
thr_fn1(void * arg) {
	struct foo foo1 = {1, 2, 3, 4};
	//foo1 = (struct foo *)malloc(sizeof(struct foo));
	//struct foo temp = {1, 2, 3, 5};
	//memcpy(foo1, &temp, sizeof(temp));	
	printfoo("thread 1:\n", &foo1);
	pthread_exit((void *)&foo1);
}

void *
thr_fn2(void * arg) {
	printf("thread 2: ID is %lu\n", pthread_self());
	printf("thread 2: ID is 0X%lx\n", pthread_self());
	pthread_exit((void *)0);
}

int
main(void) {

	int 		err;
	pthread_t	tid1, tid2;
	struct foo 	*fp;
	
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		err_quit("can not create thread 1: %s\n", strerror(err));

	err = pthread_join(tid1, (void *)&fp);
	if (err != 0)
		err_quit("can not join with thread 1: %s\n", strerror(err));

	sleep(1);
	printf("parent starting second thread\n");

	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	printf("tid2 is now %lu\n", tid2);
	printf("tid2 is now 0X%lx\n", tid2);
	if (err != 0)
		err_quit("can not create thread 2: %s\n", strerror(err));

	sleep(2);
	printfoo("parent:\n", fp);
	exit(0);
}
