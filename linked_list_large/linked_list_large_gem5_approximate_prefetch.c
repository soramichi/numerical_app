#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mmap_allocator.h"
#include "common.h"

typedef struct list_node {
  struct list_node* next;
} list_node;

list_node* c_region;
value_type* a_region;

// l1 and l2 both have the length n
list_node* merge(list_node* _l1, list_node* _l2, int n) {
  int i1 = 0, i2 = 0;
  list_node* ret;
  list_node* ptr;

  {
    list_node l1, l2;
    value_type v1, v2;
    long l1_value, l2_value;
    fetch_new(l1, v1, _l1, c_region, a_region);  // prefetch *(_l1.value)
    fetch_new(l2, v2, _l2, c_region, a_region);  // prefetch *(_l2.value)
    l1_value = v1.value;
    l2_value = v2.value;

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
    list_node l1, l2;
    value_type v1, v2;
    long l1_value, l2_value;
    fetch_new(l1, v1, _l1, c_region, a_region);  // prefetch *(_l1.value)
    fetch_new(l2, v2, _l2, c_region, a_region);  // prefetch *(_l2.value)
    l1_value = v1.value;
    l2_value = v2.value;

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

  value_type* values = (value_type*)mm_malloc_approximate(sizeof(value_type) * n);
  a_region = values;

  printf("n: %d\n", n);
  printf("next: %d, value: %d, list_node: %d\n", sizeof(root->next), sizeof(value_type), sizeof(list_node));

  printf("Size of allocated data (critical): %d\n", n * sizeof(list_node));
  printf("Size of allocated data (approximate): %d\n", n * sizeof(value_type));

  printf("critical_head: %llu\n", ptr);
  printf("approximate_head: %llu\n", values);

  for(i=0; i < n; i++) {
    values[i].value = rand() % max;
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

void print_list(list_node* l, int n) {
  int i;
  long v;
  list_node* ptr = l;

  for(i=0; i<n; i++) {
    int index = (ptr - c_region);
    v = (a_region + index)->value;
    printf("%d %ld\n", index, v);
    ptr = ptr->next;
  }
}

int confirm(list_node* l, int n) {
  int i;
  long v = 0;
  list_node* ptr = l;

  for(i=0; i<n-1; i++) {
    int index = ptr - c_region;
    long _v = (a_region + index)->value;
    if(v > _v) {
      printf("Fatal: the list is not sorted!!!\n");
      return -1;
    }
    v = _v;
    ptr = ptr->next;
  }

  printf("OK: the list of size (%d) is sorted.\n", n);
  return 0;
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

  //srand(time(NULL));
  srand(1);
  
  gettimeofday(&start, NULL);
  l = init_list_random(n, 2 * n);
  gettimeofday(&end, NULL);
  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));

  //print_list(l, n);
  gettimeofday(&start, NULL);
  l = merge_sort(l, n);
  gettimeofday(&end, NULL);
  
  printf("sort took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));
  confirm(l, n);
  //print_list(l, n);

  return 0;
}
