#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "mmap_allocator.h"

#define N_LINKS_MAX 10
const double  e = 0.000001;

struct page {
  double rank;
  double rank_next;
  int n_links;
  int links[N_LINKS_MAX];
};

int main(int argc, char* argv[]){
  int n_pages, i, j;
  struct timeval start, end;

  //srand(time(NULL));
  srand(1);

  if (argc < 2) {
    fprintf(stderr, "Usage: %s n_pages\n", argv[0]);
    return -1;
  }
  else {
    n_pages = atoi(argv[1]);
  }

  struct page* pages = (struct page*)mm_malloc_normal(sizeof(struct page) * n_pages);

  gettimeofday(&start, NULL);
  for(i=0; i<n_pages; i++) {
    pages[i].n_links = (rand() % N_LINKS_MAX) + 1;

    for(j=0; j<pages[i].n_links; j++) {
      while (1) {
	int target = (rand() % n_pages);
	if (target == i) {
	  // if the new link is to myself, do it again
	  continue;
	}
	else {
	  pages[i].links[j] = target;
	  goto ok;
	}
      }
    ok:;
    }
  }

#if defined(DEBUG)
  int* linked = malloc(sizeof(int) * n_pages);
  memset(linked, 0, sizeof(int) * n_pages);
  for(i=0; i<n_pages; i++) {
    for(j=0; j<pages[i].n_links; j++) {
      linked[pages[i].links[j]] = 1;
    }
  }

  // almost all (like 4970 out of 5000) pages are connected
  int connected = 0;
  for(i=0; i<n_pages; i++) {
    connected += linked[i];
  }
  printf("%d pages out of %d are connected\n", connected, n_pages);
#endif
  
  for(i=0; i<n_pages; i++) {
    pages[i].rank = 0.0;
    pages[i].rank_next = 0.0;
  }
  pages[0].rank = 1.0; // assume page[0] belongs to the largest clique
  
  gettimeofday(&end, NULL);
  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));


  gettimeofday(&start, NULL);
  int n_loop = 0;

  while(1) {
    n_loop++;
 
    for(i=0; i<n_pages; i++) {
      for(j=0; j<pages[i].n_links; j++) {
	int target = pages[i].links[j];
	pages[target].rank_next += pages[i].rank / pages[i].n_links;
      }
    }

    double e_max = 0;
    for(i=0; i<n_pages; i++) {
      double e_this = pages[i].rank_next - pages[i].rank; 
      if(e_this > e_max) {
	e_max = e_this;
      }
      pages[i].rank = pages[i].rank_next;
      pages[i].rank_next = 0.0;
    }

    if (e_max < e)
      goto end;
  }

 end:;
  gettimeofday(&end, NULL);
  printf("body took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));
  printf("page rank of page[0] is %0.10f\n", pages[0].rank);
  printf("calc finised with %d loops\n", n_loop);
  
  return 0;
}
