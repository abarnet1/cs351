#include <stdio.h>

int fact (int x) {
    if (x <= 1)
	return 2;
    else
	return x * fact(x-1);
}

int main (int argc, char *argv[]) {
    int i = 10,
	result;
    result = fact(i);
    printf("%d\n", result);
 return 0;
}
