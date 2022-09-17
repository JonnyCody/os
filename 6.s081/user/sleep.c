#include <stdarg.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void main(int argc, char **argv)
{
    if(argc != 2)
    {
        printf("please input number of second\n");
        exit(0);
    }
    int number  = atoi(argv[1]);
    number *= 10;
    sleep(number);
    exit(0);
}