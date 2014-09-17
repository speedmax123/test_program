#include "apue.h"

static void my_exit1(void);
static void my_exit2(void);

int
main(void) {
	if (atexit(my_exit2) != 0) {
		err_sys("can not register my_exit2");
	}
	if (atexit(my_exit1) != 0) {
		err_sys("can not register my_exit1");
	}
	printf("main is done\n");
	//exit(0);
	return(0);
}

static void
my_exit1(void) {
	printf("my_exit1 handler!\n");
}

static void
my_exit2(void) {
	printf("my_exit2 handler!\n");
}
