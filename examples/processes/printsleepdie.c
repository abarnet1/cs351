#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

int main () {
    printf("hello from psd!\n");
    fflush(stdout);
    sleep(5);
    return 0;
}