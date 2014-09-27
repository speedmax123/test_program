#include "apue.h"
#include <syslog.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/resource.h>

void
daeomnize(const char *cmd) {
    int              i, fd0, fd1, fd2;
    pid_t            pid;
    struct rlimit    rl;
    struct sigaction sa;

}
