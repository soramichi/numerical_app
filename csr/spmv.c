#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INDEX(i,j,n) ((i) * (n) + (j))

void print_double_array(double* array, int n, char* name) {
  int i;

  printf("%s:\n", name);
  for(i=0; i<n; i++) {
    printf("%.2f ", array[i]);
  }
  printf("\n");  
}

void print_integer_array(int* array, int n, char* name) {
  int i;

  printf("%s:\n", name);
  for(i=0; i<n; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");  
}

// an n x n matrix M has `num_values' values filled with randome values and all others with zero
void dense_to_csr(double* M, int n, int num_values, double** values, int** i_array, int** j_array) {
  // used only locally, no need to be retured to the caller
  int* j_array_full = (int*)malloc(sizeof(int) * num_values);

  // these arrays must be retured to the caller
  *values = (double*)malloc(sizeof(double) * num_values);
  *i_array = (int*)malloc(sizeof(int) * num_values);
  *j_array = (int*)malloc(sizeof(int) * n + 1);

  int i, j;
  int k = 0;

  for(j = 0; j<n; j++) {
    for(i = 0; i<n; i++) {
      double v = M[INDEX(i, j, n)];
      if(v != 0.0) {
	(*values)[k] = v;
	(*i_array)[k] = i;
	j_array_full[k] = j;
	k++;
      }
    }
  }

  for(k=0; k<n; k++) {
    (*j_array)[k] = -1;
  }
  for(k=0; k<num_values; k++) {
    if((*j_array)[j_array_full[k]] == -1) {
      (*j_array)[j_array_full[k]] = k;
    }
  }
  (*j_array)[n] = num_values;

  for(k=n-1 /* not n */; k>=0 ; k--) {
    if ((*j_array)[k] == -1) {
      (*j_array)[k] = (*j_array)[k+1];
    }
  }
  
  free(j_array_full);
}

void gemv_normal(int n, double* A, double* B, double* C) {
  int i, j;

  // C = AB
  for(j=0; j < n; j++) {
    volatile double tmp = 0;
    for(i=0; i < n; i++) {
      tmp += A[INDEX(i, j, n)] * B[i];
    }
    C[j] = tmp;
  }
}

void gemv_csr(int n, double* values_A, int* i_array_A, int* j_array_A /* compressed */, int num_values_A, double* B, double* C) {
  int k, j;

  for(k=0; k<n; k++) {
    double tmp = 0.0;
    for(j=j_array_A[k]; j<j_array_A[k+1]; j++) {
      tmp += values_A[j] * B[i_array_A[j]];
    }
    C[k] = tmp;
  }
}

int main(int argc, char* argv[]) {
  int n = 0, i, j;
  double ratio = 0.2; // ratio of the elements that are filled
  int loop;
  
  double *A, *B, *C;
  double *values_A;
  int *i_array_A, *j_array_A;
  int num_values_A = 0;

  struct timeval start, end;

  gettimeofday(&start, NULL);

  srand(time(NULL));
  
  if(argc < 3) {
    fprintf(stderr, "Usage: %s matrix_size num_loops\n", argv[0]);
    return 1;
  }
  else {
    n = atoi(argv[1]);
    loop = atoi(argv[2]);
  }

  A = malloc(sizeof(double) * n * n);
  B = malloc(sizeof(double) * n);
  C = malloc(sizeof(double) * n);
  
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

      // initialize B, C
      B[i] = i + 1.0;
      C[i] = 0.0;
    }
  }

  gettimeofday(&end, NULL);
  printf("init took %d ms\n", (((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec)) / 1000);

  gettimeofday(&start, NULL);
  dense_to_csr(A, n, num_values_A, &values_A, &i_array_A, &j_array_A);
  gettimeofday(&end, NULL);
  printf("convert to csr took %d ms\n", (((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec)) / 1000);
  
  // for debug
#if defined(DEBUG)
  printf("A -----------------------------:\n");
  for(j=0; j<n; j++) {
    for(i=0; i<n; i++) {
      printf("%.2f ", A[INDEX(i, j, n)]);
    }
    printf("\n");
  }
  printf("num_values: %d\n", num_values_A);
  print_double_array(values_A, num_values_A, "values");
  print_integer_array(i_array_A, num_values_A, "i_array");
  print_integer_array(j_array_A, n + 1, "j_array (compressed)");

  print_double_array(B, n, "B -----------------------------------");

  gemv_normal(n, A, B, C);
  print_double_array(C, n, "C_ref");
#endif

  // main calculation
  gettimeofday(&start, NULL);
  for(i=0; i<loop; i++) {
    gemv_csr(n, values_A, i_array_A, j_array_A, num_values_A, B, C);
  }
  gettimeofday(&end, NULL);
  printf("multiplying %d times took %d ms\n", loop, (((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec)) / 1000);
    
#if defined(DEBUG)
  print_double_array(C, n, "C_csr");
#endif  

  return 0;
}
