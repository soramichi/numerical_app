gem5:
	gcc struct_random_large_gem5_normal.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o struct_random_large_gem5_normal -O3
	gcc struct_random_large_gem5_approximate.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o struct_random_large_gem5_approximate -O3 -DUSE_APPROXIMATE

clean:
	rm -rf *~ struct_random_large_gem5_normal struct_random_large_gem5_approximate
