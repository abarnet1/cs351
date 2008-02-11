CC = gcc
CFLAGS = -g -Wall -O2
OBJS = llist.o

llist: $(OBJS)
	$(CC) $(CFLAGS) -o llist $(OBJS)

llist.o: llist.c

clean:
	rm -f *~ *.o llist
