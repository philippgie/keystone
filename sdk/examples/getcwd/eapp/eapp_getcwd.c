#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main() {

  char cwd[128];
  getcwd(cwd, sizeof(cwd));
  write(1, cwd, sizeof(cwd));

  return 0;
}
