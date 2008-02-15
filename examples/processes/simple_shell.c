#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100
#define MAXARGS 20

int parseline(const char *cmdline, char **argv);

void eval (char *cmdline) {
    char *argv[MAXARGS]; 
    int bg;
    pid_t pid;

    bg = parseline(cmdline, argv); 
    if ((pid = fork()) == 0) {   /* child runs user command */
        if (execvp(argv[0], argv) < 0) {
            printf("%s: Command not found.\n", argv[0]);
            exit(0);
        }
    }
    if (!bg) { /* parent waits for fg job to terminate */
        int status;
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitfg: waitpid error");
        }
    } 
    else { /* otherwise, don’t wait for bg job */
        printf("%d %s\n", pid, cmdline);
    }
}

int main () {
    char cmdline[MAXLINE]; 
    while (1) {
    /* read */
        printf("> ");                   
        fgets(cmdline, MAXLINE, stdin); 
        if (feof(stdin)) {
            exit(0);
        }
    /* evaluate */
        eval(cmdline);
    } /* loop! */
    return 0;
}

int parseline(const char *cmdline, char **argv) 
{
    static char array[MAXLINE]; /* holds local copy of command line */
    char *buf = array;          /* ptr that traverses command line */
    char *delim;                /* points to first space delimiter */
    int argc;                   /* number of args */
    int bg;                     /* background job? */

    strcpy(buf, cmdline);
    buf[strlen(buf)-1] = ' ';  /* replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* ignore leading spaces */
        buf++;

    /* Build the argv list */
    argc = 0;
    if (*buf == '\'') {
        buf++;
        delim = strchr(buf, '\'');
    }
    else {
        delim = strchr(buf, ' ');
    }

    while (delim) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* ignore spaces */
           buf++;

        if (*buf == '\'') {
            buf++;
            delim = strchr(buf, '\'');
        }
        else {
            delim = strchr(buf, ' ');
        }
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* ignore blank line */
        return 1;

    /* should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0) {
        argv[--argc] = NULL;
    }
    return bg;
}
