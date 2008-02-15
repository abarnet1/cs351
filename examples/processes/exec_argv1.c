#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main (int argc, char *argv[]) {
    execl(argv[1], argv[1]); // need to terminate with a 0!
    return 0;
}