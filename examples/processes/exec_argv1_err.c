#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main (int argc, char *argv[]) {
    if (execv(argv[1], &argv[1]) < 0) {
        perror("exec failed!");
    }
    return 0;
}