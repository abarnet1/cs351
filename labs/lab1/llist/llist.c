#include <stdlib.h>
#include <stdio.h>

#define EMPTY_LIST NULL

typedef struct node {
  int data;
  struct node *next;
} llnode, *llnodep;


int length (llnodep n) {
  int count = 0;
  for (; n != EMPTY_LIST; n = n->next, count++);
  return count;
}

void push (llnodep *head, int data) {
  llnodep n = (llnodep) malloc(sizeof(llnode));
  n->data = data;
  n->next = *head;
  *head = n;
}

void print_list (llnodep node) {
  printf("{ ");
  while (node != EMPTY_LIST) {
    printf("%d", node->data);
    node = node->next;
    if (node != EMPTY_LIST)
      printf(", ");
  }
  printf(" }\n");
}

/******************************************************************************
 * You should be adding code to the functions below to implement the various  *
 * described linked list functions in C.  Take care not to introduce any      *
 * memory leaks in your implementation, and test them carefully when done.    *
 *****************************************************************************/

/* Create a node with the new data, and append it to the end of the list */
void append (llnodep *head, int data) {
}

/* Returns a count of the number of times the data appears in the list */
int count_of (llnodep head, int data) {
}

/* Deallocates all the memory used by the given list, and sets its head to 
 * NULL */
void freelist (llnodep *head) {
}

/* The complementary function to push --- remove the head node of the list
 * and return its data */
int pop (llnodep *head) {
}

/* Reverse the list by rearranging next pointers and moving the head
 * pointer (your solution should be iterative) */
void reverse (llnodep *head) {
}

/* Sorts the given list in increasing order (the easier route to doing
 * this does not involve modifying any pointers) */
void sort (llnodep *head) {
}

/******************************************************************************/

/* Run some simple test cases */
int main () {
  llnodep lstA = EMPTY_LIST,
          lstB = EMPTY_LIST;

  // Build a simple list with push
  push(&lstA, 2); push(&lstA, 3); push(&lstA, 1); push(&lstA, 5);

  // Check out print_list
  print_list(lstA);
  print_list(lstB);

  // Check the length implementation
  printf("Length: %d\n", length(lstA));
  printf("Length: %d\n", length(lstB));

  // Try adding to and building a list with append
  append(&lstA, 9); append(&lstA, 3);
  append(&lstB, 20); append(&lstB, 30); append(&lstB, 40); append(&lstB, 50);
  print_list(lstA);
  print_list(lstB);

  // Check count_of
  printf("Count of 3: %d\n", count_of(lstA, 3));
  printf("Count of 0: %d\n", count_of(lstA, 0));
  printf("Count of 20: %d\n", count_of(lstB, 20));
  printf("Count of 50: %d\n", count_of(lstB, 50));

  // Try freeing up a list
  freelist(&lstA);
  printf("Length: %d\n", length(lstA));

  // Try popping off a few values
  printf("Popped: %d\n", pop(&lstB));
  printf("Popped: %d\n", pop(&lstB));
  printf("Popped: %d\n", pop(&lstB));

  // Check out reverse
  push(&lstA, -4); push(&lstA, 8); push(&lstA, 1); push(&lstA, 9);
  reverse(&lstA);
  print_list(lstA);

  // And finally, sort
  sort(&lstA);
  sort(&lstB);
  print_list(lstA);
  print_list(lstB);
  
  return 0;
}
