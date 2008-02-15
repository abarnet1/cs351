#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main (int argc, char *argv[]) {
    if (execl(argv[1], "test_arg") < 0) {
        perror("exec failed!");
    }
    return 0;
}