#include <stdio.h>
#include <stdlib.h>

#include "../bmalloc/bmalloc.c"

#define INDEX(i,j,n) ((i) * (n) + (j))

main(int argc, char* argv[]){
  int n;
  volatile double *A, *B, *C;
  int i, j, k;
  int ii, jj, kk;
  int b;

  balloc_init(&balloc, 0, 0, 1); // the 2nd and 3rd parameters do not matter here
  
  if(argc < 3) {
    fprintf(stderr, "Usage: %s n b\n", argv[0]);
  }
  else {
    n = atoi(argv[1]);
    b = atoi(argv[2]); // block size
  }

  A = balloc_malloc(&balloc, sizeof(double) * n * n, &default_attr);
  B = balloc_malloc(&balloc, sizeof(double) * n * n, &default_attr);
  C = balloc_malloc(&balloc, sizeof(double) * n * n, &default_attr);

  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      A[INDEX(i,j,n)] = i + 1.0;
      B[INDEX(i,j,n)] = j + 1.0;
      C[INDEX(i,j,n)] = 0.0;
    }
  }

  for(i=0; i < n; i+=b) {
    for(j=0; j < n; j+=b) {
      for(k=0; k < n; k+=b) {
	for(ii=i; ii < i+b; ii++){
	  for(jj=j; jj < j+b ; jj++) {
	    volatile double tmp = 0;
	    for(kk=k; kk < k+b; kk++) {
	      tmp += A[INDEX(ii, kk, n)] * B[INDEX(kk, jj, n)];
	    }
	    C[INDEX(ii, jj, n)] += tmp;
	  }
	}
      }
    }
  }

#if defined(DEBUG)
  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      printf("%f ", C[INDEX(i, j, n)]);
    }
    printf("\n");
  }
#endif

  balloc_finalize(&balloc);
}
