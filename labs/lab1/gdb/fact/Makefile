all: fact-g.out fact.out

fact-g.out: fact.c
	gcc -g -o fact-g.out fact.c

fact.out: fact.c
	gcc -o fact.out fact.c

clean:
	rm -f *.out
