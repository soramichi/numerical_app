#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../../bmalloc/bmalloc.c"

#define INDEX(i,j,n) ((i) * (n) + (j))

int main(int argc, char* argv[]){
  int n;
  volatile double *A, *B, *C;
  int i, j, ii, jj;
  int b;
  struct timeval start, end;
  
  balloc_init(&balloc, 0, 0); // the 2nd and 3rd parameters do not matter here
  
  if(argc < 3) {
    fprintf(stderr, "Usage: %s n b\n", argv[0]);
    return 1;
  }
  else {
    n = atoi(argv[1]);
    b = atoi(argv[2]); // block size
  }

  A = balloc_malloc(&balloc, sizeof(double) * n * n, &default_attr);
  B = balloc_malloc(&balloc, sizeof(double) * n, &default_attr);
  C = balloc_malloc(&balloc, sizeof(double) * n, &default_attr);

  // init
  gettimeofday(&start, NULL);
  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      A[INDEX(i,j,n)] = i + 1.0;
    }
    B[i] = i + 1.0;
    C[i] = 0.0;  
  }
  gettimeofday(&end, NULL);
  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));
  
  // C = AB
  gettimeofday(&start, NULL);
  for(i=0; i < n; i+=b) {
    for(j=0; j < n; j+=b) {
      for(ii=i; ii < i+b; ii++) {
	volatile double tmp = 0;
	for(jj=j; jj < j+b; jj++) {
	  tmp += A[INDEX(ii, jj, n)] * B[jj];
	}
	C[ii] += tmp;
      }
    }
  }
  gettimeofday(&end, NULL);
  printf("calc took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));
  
#if defined(DEBUG)
  for(i=0; i < n; i++) {
    printf("%f ", C[i]);
  }
  printf("\n");
#endif

 return 0;
}
