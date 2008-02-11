/* NOTE: This is NOT the linked list you will be modifying */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_LIST ((list) 0)

typedef struct node {
    char *value;
    struct node *next;
} listNode, *listNodePtr;

typedef listNodePtr list;

/* Function prototypes */
list cons (char *string, list l) ;
void free_list (list l) ;
void print_list (list l) ;

/*
 * main - test code for linked list 
 */
int main (int argc, char *argv[]) {
    list l = EMPTY_LIST; 

    /* try adding elements */
    l = cons("What", cons("is", cons("this", cons("list?!", EMPTY_LIST))));
    print_list(l);

    /* deallocate memory */
    free_list(l);
    return 0;
}

list cons (char *string, list l) {
    listNodePtr newNode = (listNodePtr) malloc(sizeof(listNode));
    newNode->value = (char *) malloc(strlen(string) + 1);
    strcpy(newNode->value, string);
    newNode->next = l;
    return newNode;
}

void free_list (list l) {
    listNodePtr node = l;
    if (node) {
	free_list(node->next);
	free(node->value);
	free(node);
    }
}

void print_list (list l) {
    listNodePtr node = l;
    while (node) {
	printf("%s:", node->value);
	node = node->next;
    }
    printf("\n");
}

