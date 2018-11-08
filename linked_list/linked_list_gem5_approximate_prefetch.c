#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mmap_allocator.h"

typedef struct list_node {
  //int value;
  int* value;
  struct list_node* next;
} list_node;

list_node* c_region;
int* a_region;

void print_list_n(list_node* list, int n) {
  while(n--) {
    printf("%d ", *(list->value));
    list = list->next;
  }
  printf("\n");
}

// l1 and l2 both have the length n
list_node* merge(list_node* _l1, list_node* _l2, int n) {
  int i1 = 0, i2 = 0;
  list_node* ret;
  list_node* ptr;

  {
    list_node l1;
    fetch(l1, _l1, c_region, a_region);  // prefetch *(_l1.value)
    list_node l2;
    fetch(l2, _l2, c_region, a_region);  // prefetch *(_l2.value)
    int l1_value = *(l1.value);  // cache hit
    int l2_value = *(l2.value);  // cache hit

    // what does this code do??
    if(l1_value < l2_value) {
      ptr = ret = _l1;
      _l1 = l1.next;
      i1++;
    }
    else {
      ptr = ret = _l2;
      _l2 = l2.next;
      i2++;
    }
  }

  while(i1 < n && i2 < n) {
    list_node l1;
    fetch(l1, _l1, c_region, a_region);  // prefetch *(_l1.value)
    list_node l2;
    fetch(l2, _l2, c_region, a_region);  // prefetch *(_l2.value)
    int l1_value = *(l1.value);  // cache hit
    int l2_value = *(l2.value);  // cache hit

    if(l1_value < l2_value) {
      ptr->next = _l1;
      _l1 = l1.next;
      i1++;
    }
    else {
      ptr->next = _l2;
      _l2 = l2.next;
      i2++;
    }
    ptr = ptr->next;
  }

  if (i1 == n) {
    ptr->next = _l2;
  }
  else {
    ptr->next = _l1;
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
  list_node* root = (list_node*)mm_malloc_normal(sizeof(list_node));
  list_node* ptr = root;
  int i;

  c_region = root;

  printf("Size of allocated data (critical): %d\n", n * sizeof(list_node));
  printf("Size of allocated data (approximate): %d\n", n * sizeof(int));
  
  srand(time(NULL));

  int* values_region = (int*)mm_malloc_approximate(sizeof(int) * n);
  a_region = values_region;
  
  printf("node: %llu, value: %llu\n", ptr, values_region);
  
  for(i=0; i < n; i++) {
    ptr->value = (values_region + i);
    *(ptr->value) = rand() % 10000;
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
  struct timeval start, end;

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
