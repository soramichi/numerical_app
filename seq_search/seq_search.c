#include <stdio.h>
#include <stdlib.h>

typedef struct array_node {
  unsigned int id;    // 4B
  double value;       // 8B
  unsigned int flag;  // 4B
} array_node;

void init_array(array_node* array, int n) {
  int i;

  for(i=0; i<n; i++) {
    array[i].id = i;
    array[i].value = rand() / (double)RAND_MAX;
  }
}

int main(int argc, char* argv[]) {
  int l, n, i;
  double thres = 0.5;
  int found = 0;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s array_size num_loops\n",argv[0]);
    return 1;
  }
  else {
    n = atoi(argv[1]);
    l = atoi(argv[2]);
  }

  array_node* array = (array_node*)malloc(sizeof(array_node) * n);
  init_array(array, n);
  
  while(l--) {
    found = 0;
    for(i=0; i<n; i++) {
      if(array[i].value < thres) {
	found++;
      }
    }
  }

#if defined(DEBUG)
  for(i=0; i<n; i++) {
    printf("%.2f ", array[i].value);
  }
  printf("\n");
#endif
  printf("found: %d\n", found);

  return 0;
}
