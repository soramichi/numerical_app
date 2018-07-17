#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mmap_allocator.h"

int compare(const void* _a, const void* _b) {
  const int* a = (int*)_a;
  const int* b = (int*)_b;

  return *a - *b;
}

int main(int argc, char* argv[]) {
  int n, i;
  int* values;
  struct timeval start, end;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    return 1;
  }
  else {
    n = atoi(argv[1]);
  }

  values = (int*)mm_malloc_approximate(sizeof(int) * n);
  printf("size of allocated memory: %d\n", n * sizeof(int));

  gettimeofday(&start, NULL);
  srand(time(NULL));
  for(i=0; i<n; i++) {
    values[i] = rand() % n;
  }
  gettimeofday(&end, NULL);
  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));

  gettimeofday(&start, NULL);
  qsort(values, n, sizeof(int), compare);
  gettimeofday(&end, NULL);
  printf("qsort took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));

  return 0;
}
