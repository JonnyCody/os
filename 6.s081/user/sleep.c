#include <stdarg.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void prime_proc(int *pfd)
{
    close(pfd[1]);
    int prime;
    int next_pfd[2];
    pipe(next_pfd);
    if(read(pfd[0], &prime, sizeof(int)) == sizeof(int))
    {
        printf("prime %d\n", prime);
        int pid = fork();
        // child process
        if(pid == 0)
        {
            prime_proc(next_pfd);
            exit(0);
        }
        // parent process
        else if(pid > 0)
        {
            close(next_pfd[0]);
            int number;
            while(read(pfd[0], &number, sizeof(int)) == sizeof(int))
            {
                if(number%prime)
                {
                    write(next_pfd[1], &number, sizeof(int));
                }
            }
            close(next_pfd[1]); 
            wait(0);
        }
        else
        {
            fprintf(2, "fork error");
        }
    }
    
}

void main(int argc, char **argv)
{
    int pfd[2];
    if(pipe(pfd) < 0)
    {
        fprintf(2, "cannot create a pipe fd");
        exit(-1);
    }
    int pid = fork();
    // child process
    if(pid == 0)
    {
        prime_proc(pfd);
        exit(0);
    }

    // parent process
    for(int i = 2; i <= 35; ++i)
    {
        close(pfd[0]);
        if(write(pfd[1], &i, sizeof(int)) != sizeof(int))
        {
            fprintf(2, "write pipe is wrong");

        }
    }
    close(pfd[1]);
    
    wait(0);
    exit(0);
}