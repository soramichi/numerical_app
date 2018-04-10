#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "../bmalloc/bmalloc.c"

typedef struct list_node {
  //int value;
  int* value;
  struct list_node* next;
} list_node;

void print_list_n(list_node* list, int n) {
  while(n--) {
    printf("%d ", *(list->value));
    list = list->next;
  }
  printf("\n");
}

// l1 and l2 both have the length n
list_node* merge(list_node* l1, list_node* l2, int n) {
  int i1 = 0, i2 = 0;
  list_node* ret;
  list_node* ptr;
  
  if(*(l1->value) < *(l2->value)) {
    ptr = ret = l1;
    l1 = l1->next;
    i1++;
  }
  else {
    ptr = ret = l2;
    l2 = l2->next;
    i2++;
  }

  while(i1 < n && i2 < n) {
    if(*(l1->value) < *(l2->value)) {
      ptr->next = l1;
      l1 = l1->next;
      i1++;
    }
    else {
      ptr->next = l2;
      l2 = l2->next;
      i2++;
    }
    ptr = ptr->next;
  }

  if (i1 == n) {
    ptr->next = l2;
  }
  else {
    ptr->next = l1;
  }

  return ret;
}

// for simplicity, n should be a power of two
list_node* merge_sort(list_node* list, int n) {
  if (n == 1) {
    return list;
  }
  else {
    list_node* l1 = list;
    list_node* l2 = list;
    int i;

    // `l2' points to the middle of the `list' after this loop
    for (i=0; i<n/2; i++) {
      l2 = l2->next;
    }

    l1 = merge_sort(l1, n/2);
    l2 = merge_sort(l2, n/2);

    return merge(l1, l2, n/2);
  }
}

list_node* init_list_random(int n, int max) {
  list_node* root = (list_node*)malloc(sizeof(list_node));
  list_node* ptr = root;
  int i;
  
  srand(time(NULL));

  int* values_region = (int*)balloc_malloc(&balloc, sizeof(int) * n, &default_attr);

  for(i=0; i < n; i++) {
    ptr->value = (values_region + i);
    *(ptr->value) = rand() % 10000;
    if (i < n - 1) {
      ptr->next = (list_node*)malloc(sizeof(list_node));
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
  struct timeval start, end;
  
  balloc_init(&balloc, 0, 0, 1); // the 2nd and 3rd parameters do not matter here

  if (argc < 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    fprintf(stderr, "Note: n must be a power of 2!\n");
    return 1;
  }
  else {
    n = atoi(argv[1]);
  }

  gettimeofday(&start, NULL);
  l = init_list_random(n, 2 * n);
  gettimeofday(&end, NULL);
#if defined(DEBUG)
  print_list_n(l, n);
#endif
  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));

  gettimeofday(&start, NULL);
  l = merge_sort(l, n);
  gettimeofday(&end, NULL);
#if defined(DEBUG)
  print_list_n(l, n);
#endif

  printf("sort took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));

  return 0;
}
