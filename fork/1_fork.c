#include "linux_common/common.h"

#define SHELL_PATH ("/bin/bash")

int main()
{
    if(fork()) {
        sleep(2);
        printf("parent ps, pid = %d, ppid = %d\n", getpid(), getppid());
    } else {
        printf("child ps, pid = %d, ppid = %d\n", getpid(), getppid());
        char *argv[] = {"ls", "-al"};
        execv(SHELL_PATH, argv);
    }
    return 0;
}

