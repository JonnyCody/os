#include <stdarg.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

    

// void pipetest()
// {
    // argv[0] = "wc";
    // argv[1] = 0;
    // pipe(p);
    // if(fork() == 0)
    // {
    //     close(0);
    //     dup(p[0]);
    //     close(p[0]);
    //     close(p[1]);
    //     exec("bin/wc", argv);
    // }
    // else
    // {
    //     close(p[0]);
    //     write(p[1], "hello world\n", 12);
    //     close(p[1]);
    // }
// }

// void pipetest1(void)
// {
//     int p[2];
//     char s[] = "hello world";
//     char buf[4096];
//     pipe(p);
//     if (fork() == 0) {
//         close(p[1]);
//         read(p[0], buf, sizeof(buf));
//         printf("%s\n", buf);
//         close(p[0]);
//     } else {
//         close(p[0]);
//         write(p[1], s, sizeof(s));
//         close(p[1]);
//     }
// }

int main(void)
{
    int p[2];
    // char *argv[2];
    char s[14];
    // argv[0] = "wc";
    // argv[1] = 0;
    pipe(p);
    if(fork() == 0)
    {
        close(0);
        read(p[0], s, 12);
        // dup(p[0]);
        close(p[0]);
        close(p[1]);
        write(1, s, 12);
        // exec("bin/wc", argv);
        
    }
    else
    {
        close(p[0]);
        write(p[1], "hello world\n", 12);
        close(p[1]);
    }
    exit(0);
}