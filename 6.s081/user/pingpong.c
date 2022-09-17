#include <stdarg.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
    // parent process pipe
    int pfd[2];
    // child process pipe
    int cfd[2];
    // parent process send content
    char pc[4] = "ping";
    // child process send content
    char cc[4] = "pong";
    // receive buffer
    char r[4];
    pipe(pfd);
    pipe(cfd);
    // child process
    if(fork() == 0)
    {
        while(1)
        {
            close(pfd[1]);
            close(cfd[0]);
            read(pfd[0], r, strlen(pc));
            printf("%d: recive %s\n", getpid(), r);
            sleep(10);

            write(cfd[1], cc, strlen(cc));
            close(cfd[1]);
            sleep(10);
        }
    }
    // parent process
    else
    {
        while(1)
        {
            write(pfd[1], pc, strlen(pc));
            close(pfd[1]);
            sleep(10);

            close(pfd[0]);
            close(cfd[1]);
            read(cfd[0], r, strlen(cc));
            close(pfd[0]);
            printf("%d: recive %s\n", getpid(), r);
            sleep(10);
        }
        
    }
    exit(0);
}