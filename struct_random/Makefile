vanilla:
	gcc struct_random.c -o struct_random -O3

bmalloc:
	gcc struct_random_bmalloc.c -o struct_random_bmalloc -O3 -DSKY02 -lnuma -pthread

gem5:
	gcc struct_random_gem5_normal.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o struct_random_gem5_normal -O3
	gcc struct_random_gem5_approximate.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o struct_random_gem5_approximate -O3 -DUSE_APPROXIMATE
	gcc struct_random_gem5_approximate_prefetch.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o struct_random_gem5_approximate_prefetch -O3 -DUSE_APPROXIMATE

clean:
	rm -rf *~ struct_random_bmalloc struct_random struct_random_gem5_normal struct_random_gem5_approximate struct_random_gem5_approximate_prefetch
