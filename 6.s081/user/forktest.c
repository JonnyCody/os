// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include <stdarg.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define N  1000

void
print(const char *s)
{
  write(1, s, strlen(s));
}

void
forktest(void)
{
  int n, pid;

  print("fork test\n");

  for(n=0; n<N; n++){
    pid = fork();
    if(pid < 0)
      break;
    if(pid == 0)
      exit(0);
  }

  if(n == N){
    print("fork claimed to work N times!\n");
    exit(1);
  }

  for(; n > 0; n--){
    if(wait(0) < 0){
      print("wait stopped early\n");
      exit(1);
    }
  }

  if(wait(0) != -1){
    print("wait got too many\n");
    exit(1);
  }

  print("fork test OK\n");
}

void forktest1()
{
    int pid = fork();
    // parent process
    if(pid > 0)
    {
        print("parent: child\n");
        pid = wait((int *)0);
        print("child is done\n");
    }
    else if(pid == 0)
    {
        print("child: exiting\n");
        exit(0);
    }
    else
    {
        print("fork errors\n");
    }
}
void forktest2()
{
  if(fork() == 0)
  {
    write(1, "hello ", 6);
  }
  else{
    wait(0);
    write(1, "world\n", 6);
  }
}

int
main(void)
{
  forktest2();
  exit(0);
}
