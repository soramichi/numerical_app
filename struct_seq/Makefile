vanilla:
	gcc struct_seq.c -o struct_seq -O3

bmalloc:
	gcc struct_seq_bmalloc.c -o struct_seq_bmalloc -O3 -DSKY02 -lnuma -pthread

gem5:
	gcc struct_seq_gem5_normal.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o struct_seq_gem5_normal -O3
	gcc struct_seq_gem5_approximate.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o struct_seq_gem5_approximate -O3 -DUSE_APPROXIMATE
	gcc struct_seq_gem5_approximate_prefetch.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o struct_seq_gem5_approximate_prefetch -O3 -DUSE_APPROXIMATE

clean:
	rm -rf *~ struct_seq_bmalloc struct_seq struct_seq_gem5_normal struct_seq_gem5_approximate struct_seq_gem5_approximate_prefetch
