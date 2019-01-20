all:
	make vanilla
	make bmalloc

debug:
	make vanilla_debug
	make bmalloc_debug

vanilla:
	gcc -O3 seq_search.c -o seq_search

bmalloc:
	gcc -O3 seq_search_bmalloc.c -o seq_search_bmalloc -DSKY02 -pthread -lnuma

vanilla_debug:
	gcc -O3 seq_search.c -o seq_search -DDEBUG

bmalloc_debug:
	gcc -O3 seq_search_bmalloc.c -o seq_search_bmalloc -DIMP -pthread -lnuma

gem5:
	gcc -O3 seq_search_gem5_normal.c ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o seq_search_gem5_normal -O3
	gcc -O3 seq_search_gem5_approximate.c ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o seq_search_gem5_approximate -O3 -DUSE_APPROXIMATE
	gcc -O3 seq_search_gem5_approximate_prefetch.c ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o seq_search_gem5_approximate_prefetch -O3 -DUSE_APPROXIMATE

clean:
	rm -rf *~ seq_search seq_search_bmalloc seq_search_gem5_normal seq_search_gem5_approximate
