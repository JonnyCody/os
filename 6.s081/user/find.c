#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int find(char *directory, char *filename)
{
    int fd;
    struct stat st;
    char path[512], *p;
    struct dirent de;
    // to find file in directory
    strcpy(path, directory);
    p = path+strlen(directory);
    *p++ = '/';
    strcpy(p, filename);
    // if file is in directory
    if((fd = open(path, 0)) > 0)
    {
        printf("%s\n", path);
        return 1;
    }
    // file is not in directory, so find in subdirectory
    strcpy(path, "");
    if((fd = open(directory, 0)) < 0)
    {
        fprintf(2, "find: cannot open directory %s\n", directory);
        return 0;
    }
    if(fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", directory);
        close(fd);
        return 0;
    }
    switch (st.type)
    {
    case T_FILE:
        fprintf(2, "%s is a filename, it should be a directory name\n", directory);
        break;
    case T_DIR:

        if(strlen(directory) + 1 + DIRSIZ + 1 > sizeof path)
        {
            printf("find: directory too long\n");
            break;
        }
        strcpy(path, directory);
        p = path+strlen(directory);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if(de.inum == 0)
            {
                continue;
            }
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(path, &st) < 0)
            {
                printf("ls: cannot stat %s\n", path);
                continue;
            }
            else if(st.type != T_DIR)
            {
                continue;
            }
            // if path is a subdirectory
            return find(path, filename);
        }
        break;
    default:
        break;
    }
    return 0;
}

void main(int argc, char **argv)
{
    if(argc < 3)
    {
        fprintf(2, "please input the directory and file name\n");
        exit(0);
    }
    char *directory = argv[1], *filename = argv[2];
    if(find(directory, filename) == 0)
    {
        fprintf(2, "can not find %s, in %s\n", filename, directory);
    }
    exit(0);
}