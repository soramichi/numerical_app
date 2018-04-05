#include <stdio.h>
#include <stdlib.h>

#define INDEX(i,j,n) ((i) * (n) + (j))

main(int argc, char* argv[]){
  int n;
  volatile double *A, *B, *C;
  int i, j, k;
  int ii, jj, b;
  
  if(argc < 3) {
    fprintf(stderr, "Usage: %s n b\n", argv[0]);
  }
  else {
    n = atoi(argv[1]);
    b = atoi(argv[2]); // block size
  }

  A = malloc(sizeof(double) * n * n);
  B = malloc(sizeof(double) * n * n);
  C = malloc(sizeof(double) * n * n);

  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      A[INDEX(i,j,n)] = i + 1;
      B[INDEX(i,j,n)] = j + 1;
      C[INDEX(i,j,n)] = 0;
    }
  }

  for(i=0; i < n; i+=b) {
    for(j=0; j < n; j+=b) {
      for(ii=i; ii < i+b; ii++){
	for(jj=j; jj < j+b ; jj++) {
	  volatile double tmp = 0;
	  for(k=0; k < b; k++) {
	    tmp += A[INDEX(ii, jj, n)] * B[INDEX(k, jj, n)];
	  }
	  C[INDEX(i, j, n)] += tmp;
	}
      }
    }
  }

  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      printf("%f ", C[INDEX(i, j, n)]);
    }
    printf("\n");
  }
}
