#include <stdarg.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main()
{
    mkdir("/dir");
    int fd = open("/dir/file", O_CREATE|O_WRONLY);
    close(fd);
    exit(0);
}