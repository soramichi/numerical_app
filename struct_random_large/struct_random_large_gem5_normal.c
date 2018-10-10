#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "mmap_allocator.h"

struct st_l {
  int id;         // 4
  struct st_s* p; // +8   -> 12
  double v[14];   // +112 -> 124
  int end;        // +4   -> 128
};

struct st_s {
  double v[8]; // 64
};

int main(int argc, char* argv[]) {
  int size, n_access, i;
  struct st_l* data;
  struct st_s* ptrs;
  struct timeval start, end;
  
  srand(time(NULL));

  if(argc < 3) {
    fprintf(stderr, "Usage: %s size n_access\n", argv[0]);
    return -1;
  }
  else {
    size = atoi(argv[1]);
    n_access = atoi(argv[2]);
    
  }

  printf("size: %d, n_access: %d\n", size, n_access);
  printf("Allocated critical memory: %d\n", sizeof(struct st_l) * size);
  printf("Allocated approximate memory: %d\n", sizeof(struct st_l) * size);
  data = (struct st_l*)mm_malloc_normal(sizeof(struct st_l) * size);
  ptrs = (struct st_s*)mm_malloc_normal(sizeof(struct st_s) * size);

  gettimeofday(&start, NULL);
  for(i=0; i<size; i++) {
    data[i].id = i;
    data[i].p = ptrs + i;
    ptrs[i].v[0] = (double)i;
  }
  gettimeofday(&end, NULL);

  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));

  gettimeofday(&start, NULL);
  double ans = 0.0;
  for(i=0; i<n_access; i++) {
    int target = rand() % size;
    ans += data[target].p->v[0];
  }
  gettimeofday(&end, NULL);

  printf("access took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));
  printf("ans: %f\n", ans);

  return 0;
}
