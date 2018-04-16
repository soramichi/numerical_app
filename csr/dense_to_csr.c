#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char buff[10240];
  int num_rows, num_cols, num_values;
  int *values, *i_array, *j_array, *i_array_compressed;

  fgets(buff, sizeof(buff), stdin);
  sscanf(buff, "%d %d %d", &num_rows, &num_cols, &num_values);

  printf("num_rows: %d\n", num_rows);
  printf("num_cols: %d\n", num_cols);
  printf("num_values: %d\n", num_values);

  values = (int*)malloc(sizeof(int) * num_values);
  i_array = (int*)malloc(sizeof(int) * num_values);
  j_array = (int*)malloc(sizeof(int) * num_values);
  i_array_compressed = (int*)malloc(sizeof(int) * num_rows);
  
  {
    int i, j;
    int n = 0;

    for(i = 0; i<num_rows; i++) {
      char* ret;

      ret = fgets(buff, sizeof(buff), stdin);
      if(ret == NULL) {
	fprintf(stderr, "Error: Number of num_rows declared to be %d, but only %d num_rows given\n", num_rows, i+1);
	return 1;
      }

      char* ptr = buff;
      for(j = 0; j < num_cols; j++) {
	int v = atoi(ptr);
	if(v != 0) {
	  values[n] = v;
	  i_array[n] = i;
	  j_array[n] = j;
	  n++;
	}
	ptr = strchr(ptr+1, ' ');
      }
    }
  }

  {
    int i;

    printf("values:\n");
    for(i=0; i<num_values; i++) {
      printf("%d ", values[i]);
    }
    printf("\n");

    printf("i_array:\n");
    for(i=0; i<num_values; i++) {
      printf("%d ", i_array[i]);
    }
    printf("\n");
    

    printf("i_array_compressed:\n");
    for(i=0; i<num_rows; i++) {
      i_array_compressed[i] = -1; 
    }
    for(i=0; i<num_values; i++) {
      if(i_array_compressed[i_array[i]] == -1) {
	i_array_compressed[i_array[i]] = i;
      }
    }
    for(i=0; i<num_rows; i++) {
      printf("%d ", i_array_compressed[i]);
    }
    printf("\n");

    printf("j_array:\n");
    for(i=0; i<num_values; i++) {
      printf("%d ", j_array[i]);
    }
    printf("\n");
  }
  
  return 0;
}
