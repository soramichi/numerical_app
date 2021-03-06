#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mmap_allocator.h"
#include "common.h"

struct person {
  id_type id;
  SCORE_DECLARATION;
};

int main(int argc, char* argv[]) {
  int size, n_access, i, k = 1;
  struct person* people;
  struct timeval start, end;

  if(argc < 3) {
    fprintf(stderr, "Usage: %s size n_access\n", argv[0]);
    return -1;
  }
  else {
    size = atoi(argv[1]);
    n_access = atoi(argv[2]);
    
  }

  printf("size: %d, n_access: %d\n", size, n_access);
  printf("id_type: %d, score_type: %d, person: %d\n", sizeof(id_type), sizeof(score_type), sizeof(struct person));
  printf("Allocated memory: %d\n", sizeof(struct person) * size);
  people = (struct person*)mm_malloc_normal(sizeof(struct person) * size);

  gettimeofday(&start, NULL);
  for(i=0; i<size; i++) {
    people[i].id = (id_type)(i % 100);
    people[i].score = (double)(i % 100);
  }
  gettimeofday(&end, NULL);

  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));

  gettimeofday(&start, NULL);
  unsigned long ans_id;
  double ans;
  while(k--) {
    ans_id = 0;
    ans = 0.0;
    for(i=0; i<n_access; i++) {
      int target = i & (size - 1); // assume size % 2 == 0
      ans_id += people[target].id;
      ans += (double)people[target].score;
    }
  }
  gettimeofday(&end, NULL);

  printf("access took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));
  printf("ans_id: %lu\n", ans_id);
  printf("ans: %f\n", ans);

  return 0;
}
