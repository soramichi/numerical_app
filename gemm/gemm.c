#include <stdio.h>
#include <stdlib.h>

#define INDEX(i,j,n) ((i) * (n) + (j))

main(int argc, char* argv[]){
  int n;
  volatile double *A, *B, *C;
  int i, j, k;
  
  if(argc < 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
  }
  else {
    n = atoi(argv[1]);
  }

  A = malloc(sizeof(double) * n * n);
  B = malloc(sizeof(double) * n * n);
  C = malloc(sizeof(double) * n * n);

  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      A[INDEX(i,j,n)] = i + 1.0;
      B[INDEX(i,j,n)] = j + 1.0;
      C[INDEX(i,j,n)] = 0.0;
    }
  }
  
  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      volatile double tmp = 0;
      for(k=0; k < n; k++) {
	tmp += A[INDEX(i, k, n)] * B[INDEX(k, j, n)];
      }
      C[INDEX(i, j, n)] = tmp;
    }
  }

  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      printf("%f ", C[INDEX(i, j, n)]);
    }
    printf("\n");
  }
}
