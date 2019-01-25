#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "../../bmalloc/bmalloc.c"

struct person {
  int id;
  //  double score;
  double* score;
};

int main(int argc, char* argv[]) {
  int size, n_access, i;
  struct person* people;
  double* values;
  struct timeval start, end;

  balloc_init(&balloc, 0, 0); // the 2nd and 3rd parameters do not matter here
  
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
  printf("Allocated critical memory: %d\n", sizeof(struct person) * size);
  printf("Allocated approximate memory: %d\n", sizeof(double) * size);

  people = (struct person*)malloc(sizeof(struct person) * size);
  values = (double*)balloc_malloc(&balloc, sizeof(double) * size, &default_attr);

  printf("people: %llu, values: %llu\n", people, values);

  gettimeofday(&start, NULL);
  for(i=0; i<size; i++) {
    people[i].id = i;
    people[i].score = values + i;
    *(people[i].score) = (double)i;
  }
  gettimeofday(&end, NULL);

  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));

  gettimeofday(&start, NULL);
  double ans = 0.0;
  for(i=0; i<n_access; i++) {
    int target = rand() % size;
    ans += *(people[target].score);
  }
  gettimeofday(&end, NULL);

  printf("access took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));
  printf("ans: %f\n", ans);

  return 0;
}
