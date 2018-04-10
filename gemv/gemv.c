#include <stdio.h>
#include <stdlib.h>

#define INDEX(i,j,n) ((i) * (n) + (j))

int main(int argc, char* argv[]){
  int n;
  volatile double *A, *B, *C;
  int i, j, k;
  
  if(argc < 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    return 1;
  }
  else {
    n = atoi(argv[1]);
  }

  A = malloc(sizeof(double) * n * n);
  B = malloc(sizeof(double) * n);
  C = malloc(sizeof(double) * n);

  // init
  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      A[INDEX(i,j,n)] = i + 1.0;
      B[i] = j + 1.0;
      C[i] = 0.0;
    }
  }

  // C = AB
  for(i=0; i < n; i++) {
    volatile double tmp = 0;
    for(j=0; j < n; j++) {
      tmp += A[INDEX(i, j, n)] * B[j];
    }
    C[i] = tmp;
  }

#if defined(DEBUG)
  for(i=0; i < n; i++) {
    printf("%f ", C[i]);
  }
  printf("\n");
#endif

 return 0;
}
