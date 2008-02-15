#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
    if (fork()==0) {
        execl("printsleepdie", 0);
    }
    wait(NULL);
    printf("Done exec-ing psd!\n");
    printf("Yay!\n");
    return 0;
}