#include "apue.h"
#include <fcntl.h>

void print_stdio(const char *, FILE *);

int
main(void) {
	FILE * fp;
	fputs("enter any character here\n", stdout);
	if(getchar() == EOF) {
		err_sys("getchar error");
	}
	fputs("one line to standard error\n", stderr);
	
	print_stdio("stdin", stdin);
	print_stdio("stdout", stdout);
	print_stdio("stderr", stderr);

	if((fp = fopen("/etc/rc.local", "r")) == NULL) {
		err_sys("fopen error");
	}

	if(getc(fp) == EOF) {
		err_sys("getc error");
	}

	print_stdio("~/.vimrc", fp);
	fclose(fp);
	exit(0);
}

void
print_stdio(const char * name, FILE * fp) {
	printf("stream - %s, ", name);
/**
 * The following is nonportable
 */
/**
 * result:
 * stream - stdin, line buffered, buffer size = 1024
 * stream - stdout, line buffered, buffer size = 1024
 * stream - stderr, unbuffered, buffer size = 1
 * stream - ~/.vimrc, full buffered, buffer size = 4096
 */
	if(fp -> _IO_file_flags & _IO_UNBUFFERED) {
		printf("unbuffered");
	}
	else if(fp -> _IO_file_flags & _IO_LINE_BUF) {
		printf("line buffered");
	}
	else {
		/* if neither above */
		printf("full buffered");
	}
	printf(", buffer size = %lu\n", fp -> _IO_buf_end - fp -> _IO_buf_base);
}
