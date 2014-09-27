#include "apue.h"
#include <limits.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int
makethread(void *(*fn)(void *), void * arg) {

	int					err;
	pthread_t			tid;
	pthread_attr_t		attr;
	
	err = pthread_attr_init(&attr);
	if (err != 0)
		return(err);
	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (err == 0)
		err = pthread_create(&tid, &attr, fn, arg);
	pthread_attr_destroy(&attr);
	return(err);
}

extern char **environ;

pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void
thread_init(void) {
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&env_mutex, &attr);
	pthread_mutexattr_destroy(&attr);
}

int
getenv_r(const char *name, char *buf, int buflen) {
	
	int i, len, olen;
	pthread_once(&init_done, thread_init);
	len = strlen(name);
	pthread_mutex_lock(&env_mutex);
	for (i = 0; environ[i] != NULL; i++) {
		if ((strncmp(name, environ[i], len) == 0) &&
				environ[i][len] == '=') {
			olen = strlen(&environ[i][len + 1]);
			if (olen >= buflen) {
				pthread_mutex_unlock(&env_mutex);
				return(ENOSYS);
			}
			strcpy(buf, &environ[i][len + 1]);
			pthread_mutex_unlock(&env_mutex);
			return(0);
		}
	}
	pthread_mutex_unlock(&env_mutex);
	return(ENOENT);
}

pthread_key_t key;

static void
thread_init2(void) {
	pthread_key_create(&key, free);
}

char *
getenv_rr(const char *name) {
	
	int i, len;
	char *envbuf;

	pthread_once(&init_done, thread_init2);
	pthread_mutex_lock(&env_mutex);
	envbuf = (char *)pthread_getspecific(key);
	if (envbuf == NULL) {
		envbuf = malloc(ARG_MAX);
		if (env_buf == NULL) {
			pthread_mutex_unlock(&env_mutex);
			return(NULL);
		}
		pthread_setspecific(key, envbuf);
	}
	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++) {
		if ((strncmp(name, environ[i], len) == 0) &&
				(environ[i][len] = '=')) {
			strcpy(envbuf, &environ[i][len + 1]);
			pthread_mutex_unlock(&mutex);
			return envbuf;
		}
	}
	pthread_mutex_unlock(&mutex);
	return(NULL);
}
