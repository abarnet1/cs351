#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

int main () {
    execl("printsleepdie", 0);
    printf("Done exec-ing psd!\n");
    printf("Yay!\n");
    return 0;
}