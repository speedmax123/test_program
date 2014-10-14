#include "apue.h"
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

char        buf[500000];

void
clr_fl(int fd, int flags) {
    int     val;
    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        err_sys("fcntl F_GETFL errno");
    }

    val &= ~flags;

    if (fcntl(fd, F_SETFL, val) < 0) {
        err_sys("fcntl F_SETFL errno");
    }
}

void
set_fl(int fd, int flags) {
    int     val;
    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        err_sys("fcntl F_GETFL errno");
    }

    val |= flags;

    if (fcntl(fd, F_SETFL, val) < 0) {
        err_sys("fcntl F_SETFL errno");
    }
}

int
main(void) {

    int     ntowrite = 0, nwrite = 0;
    char    *ptr = NULL; 

    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes, error msg is %s\n", ntowrite, strerror(errno));

    set_fl(STDOUT_FILENO, O_NONBLOCK); /* set nonblocking */

    ptr = buf;
    while (ntowrite > 0) {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "mwrite = %d, errno = %d\n", nwrite, errno);

        if (nwrite > 0) {
            ptr += nwrite;
            ntowrite -= nwrite;
        }
    }
    clr_fl(STDOUT_FILENO, O_NONBLOCK);  /* clear non_blocking */
    exit(0);
}

