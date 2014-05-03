#include "apue.h"

static void err_doit(int, int, const char *, va_list);

/*
 * Nonfatal error related to a system call
 * Print a message and return
 */

void
err_ret(const char * fmt, ...)
{
	va_list 	ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
}
	
/*
 * Fatal error related to a system call
 * print a message and terminate
 */

void
err_sys(const char * fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 * Fatal error related to a system call
 * Error code passed as explict parameter
 * Print a message and terminate
 */

void
err_exit(int error, const char * fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, error, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 * Fatal error related to a system call
 * print a message, dump core , and terminate
 */

void
err_dump(const char * fmt, ...)
{
	va_list ap;
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	abort();	/* core dump and terminate */
	exit (1);
}

/*
 * Nofatal error unrelated to a system call
 * print a message and return
 */
void
err_msg(const char * fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
}

/*
 * Fatal error unrelated to a system call
 * print a message and terminate
 */
void
err_quit(const char * fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
	exit(1);
}

/*
 * print a message and return to caller
 * caller specifies "errnoflag"
 */
static void
err_doit(int errnoflag, int error, const char * fmt, va_list ap)
{
	char buf[MAXLINE];
	vsnprintf(buf, MAXLINE, fmt, ap);
	
	if(errnoflag)
	{
		snprintf(buf+strlen(buf), MAXLINE - strlen(buf), ": %s", strerror(error));
	}
	strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);		/* in case stdout and stderr are the same */
	fflush(NULL);			/* fflushes all stdio output streams */
}
