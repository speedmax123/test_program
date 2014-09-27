#include <stdio.h>
#include <sys/resource.h>

int
main(void) {
#ifdef RLIMIT_NOFILE
	printf("rlimit_nofile is %d\n", RLIMIT_NOFILE);
#endif
	return(0);
}
