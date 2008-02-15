#include <stdio.h>
#include <stdarg.h>

int main (int argc, char *argv[]) {
    int i;
    char **p;
    
    for (i=0; i<argc; i++) {
        printf("%s\n", argv[i]);
    }
    
    /* this SHOULD work, iff argv is null terminated */
    p = argv;
    while (*p) {
        printf("%s\n", *p++);
    }
    
    return 0;
}