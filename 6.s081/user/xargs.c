#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int read_line(char* buf)
{
    int num_of_read = 0;
    char ch;
    while(1)
    {
        if(read(0, &ch, 1) == 1)
        {
            ++num_of_read;
            *buf++ = ch;
            if(ch == '\n' || ch == '\r')
            {
                break;
            }
        }
        else
        {
            break;
        }

    }
    *buf = '\0';
    return num_of_read;
    // char c;
    // while (1) {
    //     int num = read(0, &c, 1);
    //     if (num < 1)    return 0;
    //     if (c == '\n' || c == '\r')
    //         break;
    //     *buf++ = c;
    // }
    // *buf = '\0';
    // return 1;
}

int main(int argc, char *argv[]) 
{
    if(argc < 2)
    {
        fprintf(2, "xargs [options] [command [initial-arguments]]\n");
        exit(1);
    }
    char* argv2[MAXARG], buf[512];
    for(int i = 1; i < argc; ++i)
    {
        argv2[i-1] = argv[i];
    }
    while(read_line(buf))
    {
        // printf("%s\n", buf);
        if(fork() == 0)
        {
            argv2[argc - 1] = buf;
            exec(argv2[0], argv2);
            exit(0);
        }
        else
        {
            wait(0);
        }
    }
    exit(0);
}