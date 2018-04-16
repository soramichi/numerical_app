#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INDEX(i,j,n) ((i) * (n) + (j))

void print_double_array(volatile double* array, int n, char* name) {
  int i;

  printf("%s:\n", name);
  for(i=0; i<n; i++) {
    printf("%.2f ", array[i]);
  }
  printf("\n");  
}

void print_integer_array(volatile int* array, int n, char* name) {
  int i;

  printf("%s:\n", name);
  for(i=0; i<n; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");  
}

// an n x n matrix M has `num_values' values filled with randome values and all others with zero
void dense_to_csr(volatile double* M, int n, int num_values, double** values, int** i_array, int** j_array) {
  // used only locally, no need to be retured to the caller
  int* i_array_full = (int*)malloc(sizeof(int) * num_values);

  // these arrays must be retured to the caller
  *values = (double*)malloc(sizeof(double) * num_values);
  *i_array = (int*)malloc(sizeof(int) * n);
  *j_array = (int*)malloc(sizeof(int) * num_values);

  int i, j;
  int k = 0;

  for(i = 0; i<n; i++) {
    for(j = 0; j<n; j++) {
      double v = M[INDEX(i, j, n)];
      if(v != 0.0) {
	(*values)[k] = v;
	i_array_full[k] = i;
	(*j_array)[k] = j;
	k++;
      }
    }
  }

  for(i=0; i<n; i++) {
    (*i_array)[i] = -1; 
  }
  for(i=0; i<num_values; i++) {
    if((*i_array)[i_array_full[i]] == -1) {
      (*i_array)[i_array_full[i]] = i;
    }
  }

  free(i_array_full);
}

void gemm_normal(double* A, double* B, double* C, int n) {
  int i, j, k;

  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      volatile double tmp = 0;
      for(k=0; k < n; k++) {
	tmp += A[INDEX(i, k, n)] * B[INDEX(k, j, n)];
      }
      C[INDEX(i, j, n)] = tmp;
    }
  }
}

void gemm_csr(int n,
		 double* values_A, int* i_array_A, int* j_array_A, int num_values_A,
		 double* values_B, int* i_array_B, int* j_array_B, int num_values_B)
{
  
}

int main(int argc, char* argv[]) {
  int n = 0, i, j;
  double ratio = 0.2; // ratio of the elements that are filled

  volatile double *A, *B, *C;
  double *values_A, *values_B;
  int *i_array_A, *i_array_B;
  int *j_array_A, *j_array_B;
  int num_values_A = 0, num_values_B = 0;

  srand(time(NULL));

  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
    }
  }
  
  if(argc < 2) {
    fprintf(stderr, "Usage: %s n\n", argv[0]);
    return 1;
  }
  else {
    n = atoi(argv[1]);
  }

  A = malloc(sizeof(double) * n * n);
  B = malloc(sizeof(double) * n * n);
  C = malloc(sizeof(double) * n * n);
  
  for(i=0; i < n; i++) {
    for(j=0; j < n; j++) {
      // initialize A
      if(rand() / (double)RAND_MAX < ratio) {
	A[INDEX(i,j,n)] = i + j + 1.0;
	num_values_A++;
      }
      else {
	A[INDEX(i,j,n)] = 0.0;
      }

      // initialize B
      if(rand() / (double)RAND_MAX < ratio) {
	B[INDEX(i,j,n)] = i + j + 1.0;
	num_values_B++;
      }
      else {
	B[INDEX(i,j,n)] = 0.0;
      }

      // initialize C
      C[INDEX(i, j, n)] = 0.0;
    }
  }

  dense_to_csr(A, n, num_values_A, &values_A, &i_array_A, &j_array_A);
  dense_to_csr(B, n, num_values_B, &values_B, &i_array_B, &j_array_B);

  // for debug
  /*
  printf("A -----------------------------\n");
  for(i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      printf("%.2f ", A[INDEX(i, j, n)]);
    }
    printf("\n");
  }
  printf("num_values_A: %d\n", num_values_A);
  print_double_array(values_A, num_values_A, "values_A");
  print_integer_array(i_array_A, n, "i_array_A");
  print_integer_array(j_array_A, num_values_A, "j_array_A");

  printf("B -----------------------------\n");
  for(i=0; i<n; i++) {
    for(j=0; j<n; j++) {
      printf("%.2f ", B[INDEX(i, j, n)]);
    }
    printf("\n");
  }
  printf("num_values: %d\n", num_values_B);
  print_double_array(values_B, num_values_B, "values");
  print_integer_array(i_array_B, n, "i_array");
  print_integer_array(j_array_B, num_values_B, "j_array");
  */
  
  return 0;
}
