#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mmap_allocator.h"
#include "common.h"

typedef struct list_node {
  struct list_node* next;
  VALUE_DECLARATION;
} list_node;

__attribute__((noinline)) void touch_list(volatile list_node* list, int n) {  
  int i;

  for (i=0; i<n-1; i++) {
    list = list->next;
  }
}

list_node* init_list_random(int n, int max) {
  list_node* root = (list_node*)mm_malloc_normal(sizeof(list_node));
  list_node* ptr = root;
  int i;

  printf("Size of allocated data: %d\n", n * sizeof(list_node));

  srand(1);

  for(i=0; i < n; i++) {
    ptr->value = rand() % max;
    if (i < n - 1) {
      ptr->next = (list_node*)mm_malloc_normal(sizeof(list_node));
      ptr = ptr->next;
    }
    else {
      ptr->next = NULL;
    }
  }

  return root;
}

int main(int argc, char* argv[]){
  int n;
  list_node* l;
  list_node *p;
  struct timeval start, end;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    fprintf(stderr, "Note: n must be a power of 2!\n");
    return 1;
  }
  else {
    n = atoi(argv[1]);
  }

  printf("n: %d\n", n);
  printf("next: %d, value: %d, list_node: %d\n", sizeof(l->next), sizeof(value_type), sizeof(list_node));
  
  gettimeofday(&start, NULL);
  l = init_list_random(n, 2 * n);
  gettimeofday(&end, NULL);
  
  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));

  {
    int N = 10, i;

    gettimeofday(&start, NULL);
    for(i=0; i<N; i++) {
      touch_list(l, n);
    }
    gettimeofday(&end, NULL);
  }

  printf("touch took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));
  
  return 0;
}
