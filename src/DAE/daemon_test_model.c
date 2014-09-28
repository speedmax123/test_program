#include "apue.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/stat.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE "S_IRUSR|S_IWUSR|S_IRUSR|S_IROTH"

void
daeomnize(const char *cmd) {
    int              i, fd0, fd1, fd2;
    pid_t            pid;
    struct rlimit    rl;
    struct sigaction sa;

//clear file creation mask
    umask(0);
//get the maxium number of file descriptors
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) {
        err_quit("%s: can't get file limit", cmd);
    }
//become a session leader to lose control of TTY
    if ((pid = fork()) < 0) {
        err_quit("%s: can not fork", cmd);
    }
    else if (pid != 0) /* parent */{
        exit(0);
    }
    setsid();
//enable futhure open won't allocate new TTYs
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("%s: can't ignore SIGHUP");
    if ((pid = fork()) < 0) {
        err_quit("%s: can't fork", cmd);
    }
    else if (pid == 0) {
        /* parent */
        exit(0);
    }
//change the current working directory to the root so we don't prevent file system from being unmounted
    if (chdir("/") < 0) {
        err_quit("%s: can't change directory to /");
    }
//close all file descriptors
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; i++) {
        close(i);
    }
//Attach file descriptor 0, 1, 2 to /dev/null
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
//initilize the log file
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "expected file descriptor %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}

int
already_running(void) {
	int	    fd;
    char    buf[16];

    fd = open(LOCKFILE, O_RDWR|O_CREAT, LOCKMODE);
    if (fd < 0) {
        syslog(LOG_ERR, "can not open %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }
    if (lockfile(fd) < 0) {
        if (errno == EACCES || errno == EAGAIN) {
            close(fd);
            return(1);
        }
        syslog(LOG_ERR, "can not lock %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }
    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf) + 1);
    return(0);
}

int
main(int argc, char *argv[]) {
    /*
    if (argc != 2) {
        err_quit("%s: ./daemon_stest_model.out CMD", "usage");
    }
    else {
        printf("current command is %s\n", argv[1]);
    }
    */
    daeomnize("");
    return(0);
}
