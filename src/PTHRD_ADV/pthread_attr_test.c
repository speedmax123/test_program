#include "apue.h"
#include <stdio.h>
#include <pthread.h>

int
main(void) {

#ifdef _POSIX_THREAD_ATTR_STACKADDR
	printf("posix_thread_attr_stackaddr defined\n");
#endif	//_POSIX_THREAD_ATTR_STACKSIZE
#ifdef _POSIX_THREAD_ATTR_STACKSIZE
	printf("posix_thread_attr_stacksize defined\n");
#endif
#ifdef _POSIX_THREAD_PROCESS_SHARED
	printf("posix_thread_process_shared defined\n");
#endif
#ifdef _SC_THREAD_PROCESS_SHARED
	printf("sc_thread_process_shared defined\n");
#endif
#ifdef PTHREAD_PROCESS_PRIVATE
	printf("sc_thread_process_private defined\n");
#endif
#ifdef _POSIX_THREAD_SAFE_FUNCTIONS
	printf("posix_thread_safe_function defined\n");
#endif
#ifdef _SC_THREAD_KEYS_MAX
	printf("pthread_keys_max is %d\n", _SC_THREAD_KEYS_MAX);
#endif
	printf("pthread_destructor_iterations is %d\n", _SC_THREAD_DESTRUCTOR_ITERATIONS);
	return 0;
}
