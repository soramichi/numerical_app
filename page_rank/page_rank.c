#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define N_LINKS_MAX 10
const double  e = 0.000001;

struct page {
  double rank;
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

  struct page* pages = (struct page*)malloc(sizeof(struct page) * n_pages);

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
    rank_next[i] = 0.0;
  }
  pages[0].rank = 1.0; // assume page[0] belongs to the largest clique
  
  gettimeofday(&end, NULL);
  printf("init took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));


  gettimeofday(&start, NULL);
  double* rank_next = malloc(sizeof(double) * n_pages);
  int n_loop = 0;

  while(1) {
    n_loop++;
 
    for(i=0; i<n_pages; i++) {
      for(j=0; j<pages[i].n_links; j++) {
	rank_next[pages[i].links[j]] += pages[i].rank / pages[i].n_links;
      }
    }

    double e_max = 0;
    for(i=0; i<n_pages; i++) {
      double e_this = rank_next[i] - pages[i].rank; 
      if(e_this > e_max) {
	e_max = e_this;
      }
    }

    if (e_max < e)
      goto end;

    for(i=0; i<n_pages; i++) {
      pages[i].rank = rank_next[i];
      rank_next[i] = 0.0;
    }
  }

 end:;
  gettimeofday(&end, NULL);
  printf("body took %d us\n", ((end.tv_sec * 1000ULL * 1000ULL) + end.tv_usec) - ((start.tv_sec * 1000ULL * 1000ULL) + start.tv_usec));
  printf("page rank of page[0] is %0.10f\n", pages[0].rank);
  printf("calc finised with %d loops\n", n_loop);
  
  return 0;
}
