#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mmap_allocator.h"

typedef struct array_node {
  unsigned long id;   // 4B
  //  double* value;      // 8B
} array_node;

int main(int argc, char* argv[]) {
  int l, n, i;
  double thres = 0.5;
  int found = 0;
  struct timeval start, end;
  
  if (argc < 3) {
    fprintf(stderr, "Usage: %s array_size num_loops\n",argv[0]);
    return 1;
  }
  else {
    n = atoi(argv[1]);
    l = atoi(argv[2]);
  }

  printf("Size of an array_node: %d\n", sizeof(array_node));
  printf("Size of allocated memory: %d\n", sizeof(array_node) * n);
  
  gettimeofday(&start, NULL);

  srand(time(NULL));
  array_node* array = (array_node*)mm_malloc_normal(sizeof(array_node) * n);
  double* values_region = (double*)mm_malloc_approximate(sizeof(double) * n);
  printf("critical_head: %llu\n", array);
  printf("approximate_head: %llu\n", values_region);
  for(i=0; i<n; i++) {
    array[i].id = i;
    values_region[i] = rand() / (double)RAND_MAX;
  }

  gettimeofday(&end, NULL);
  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));

  gettimeofday(&start, NULL);
  while(l--) {
    found = 0;
    for(i=0; i<n; i++) {
      double value;
      struct array_node n;
      fetch_new(n, value, array + i, array, values_region);
      if(value < thres) {
	found++;
      }
    }
  }
  gettimeofday(&end, NULL);
  printf("seq_search took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));
  
#if defined(DEBUG)
  for(i=0; i<n; i++) {
    printf("%.2f ", array[i].value);
  }
  printf("\n");
#endif
  printf("found: %d\n", found);

  return 0;
}
