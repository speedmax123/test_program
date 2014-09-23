#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define handler_error_en(en, msg) \
	do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handler_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct thread_info {
	pthread_t thread_id;
	int		 thread_num;
	char * 	 argv_string;
};

typedef struct thread_info * p_thread_info;

/**
 * thread start function: display address near top of stack,
 * and return upper-cased copy of argument string
 */

static void *
thread_start(void * arg) {

	p_thread_info tinfo = arg;
	char * uargv, *p;
	
	printf("Thread %d: top of stack near %p; arg_string = %s\n",
			tinfo -> thread_num, 
			&p,
			tinfo -> argv_string);

	uargv = strdup(tinfo -> argv_string);
	if(uargv == NULL) {
		handler_error("strdup");
	}

	for(p = uargv; *p != '\0'; p++) {
		*p = toupper(*p);
	}

	return uargv;
}

int main(int argc, char * argv[]) {

	int s, tnum, opt, num_threads;
	p_thread_info tinfo;
	pthread_attr_t attr;
	int stack_size;
	void * res;
	
	/* the "-s" option specifies a stack size for our threads */
	stack_size = -1;
	while((opt = getopt(argc, argv, "s:")) != -1) {
		switch(opt) {
		case 's':
			stack_size = strtoul(optarg, NULL, 0);
			break;

		default:
			fprintf(stderr, "Usage: %s [-s stack-size] arg...\n",
				argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	num_threads = argc - optind;
	printf("num_thread is %d, and optind is %d\n", num_threads, optind);
	
	/* initilize thread creation attributes */
	s = pthread_attr_init(&attr);
	if(s != 0) {
		handler_error_en(s, "pthread_attr_init");
	}
	
	if(stack_size > 0) {
		s = pthread_attr_setstacksize(&attr, stack_size);
		if(s != 0)
			handler_error_en(s, "pthread_attr_setstacksize");
	}
	
	/* allocate memory for pthread_create() arguments */
	
	tinfo = calloc(num_threads, sizeof(struct thread_info));
	if(tinfo == NULL) {
		handler_error("calloc");
	}
	
	/* create one thread for each command-line argument */
	
	for(tnum = 0; tnum < num_threads; tnum++) {
		tinfo[tnum].thread_num = tnum + 1;
		tinfo[tnum].argv_string = argv[optind + tnum];
		
		/* the pthread_create() call stores the thread ID into corresponding element of tinfo[] */
		s = pthread_create(&tinfo[tnum].thread_id, &attr, &thread_start, &tinfo[tnum]);
		if(s != 0) {
			handler_error_en(s, "pthread_create");
		}
	}
		
	/* destroy the thread attribution objects, since it is no longer needed */
	s = pthread_attr_destroy(&attr);
	if(s != 0) {
		handler_error_en(s, "pthread_attr_destroy");
	}
	
	/* now join with each thread, and display its return value */
	for(tnum = 0; tnum < num_threads; tnum++) {
		s = pthread_join(tinfo[tnum].thread_id, &res);
		if(s != 0) {
			handler_error_en(s, "pthread_join");
		}
		printf("joined with thread %d, return value was %s\n",
				tinfo[tnum].thread_num, (char *)res);
		free(res);
	}

	free(tinfo);
	exit(EXIT_FAILURE);
}

