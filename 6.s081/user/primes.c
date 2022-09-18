#include "kernel/types.h"
#include "user/user.h"

void prime_proc(int* pfd)
{
    close(pfd[1]);
    int prime, size_of_int = sizeof(int);
    // receive the first number must be prime
    if(read(pfd[0], &prime, size_of_int) == size_of_int)
    {
        printf("prime %d\n", prime);
    }
    // if can not receive number, interpret the progress is over
    else
    {
        return;
    }
    int next_pfd[2];
    if(pipe(next_pfd) < 0)
    {
        fprintf(2, "pid is %d, pipe occur error\n", getpid());
        exit(-1);
    }
    int pid = fork();
    // child process continue to receive the rest number
    if(pid == 0)
    {
        prime_proc(next_pfd);
        exit(0);
    }
    // current process to write number to child process
    int number;
    while(read(pfd[0], &number, size_of_int) == size_of_int)
    {
        if(number%prime)
        {
            write:
            if(write(next_pfd[1], &number, size_of_int) != size_of_int)
            {
                fprintf(2, "pid: %d, write %d to pfd occur error", getpid(), number);
                goto write;
            }
        }
    }
    close(next_pfd[1]);
    wait(0);
}

void main(void)
{
    int pfd[2];
    int size_of_int = sizeof(int);
    if(pipe(pfd) < 0)
    {
        fprintf(2, "pid is %d, pipe occur error\n", getpid());
        exit(-1);
    }
    int pid = fork();
    // child process handle prime
    if(pid == 0)
    {
        prime_proc(pfd);
        exit(0);
    }
    for(int i = 2; i <= 35; ++i)
    {
        if(write(pfd[1], &i, size_of_int) != size_of_int)
        {
            fprintf(2, "pid: %d, write %d to pfd occur error", getpid(), i);
            --i;
        }
    }
    close(pfd[1]);
    wait(0);
    exit(0);
}