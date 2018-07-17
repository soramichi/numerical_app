all:
	gcc -O3 qsort.c -o qsort

gem5:
	gcc -O3 qsort_gem5_normal.c ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o qsort_gem5_normal
	gcc -O3 qsort_gem5_approximate.c ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o qsort_gem5_approximate

clean:
	rm -rf qsort qsort_gem5_normal qsort_gem5_approximate *~
