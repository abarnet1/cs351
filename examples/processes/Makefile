SRC_FILES = csapp_forks.c exec_argv1.c exec_psd.c exec_psd_imp.c fork_simple.c fork_exam_eg.c fork_exam_eg_imp.c print_exec_args.c printsleepdie.c
EXECS     = ${SRC_FILES:.c=}
O_FILES   = $(SRC_FILES:%.c=%.o)

CC        = gcc
CFLAGS    = -Wall -O2
LDFLAGS   = 
LDLIBS    = 

all: $(EXECS)

clean:
	rm -f $(EXECS)
