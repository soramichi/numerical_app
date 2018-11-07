vanilla:
	gcc page_rank.c -O3 -o page_rank

debug:
	gcc page_rank.c -O3 -o page_rank -DDEBUG

gem5:
	gcc page_rank_gem5_normal.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o page_rank_gem5_normal -g
	gcc page_rank_gem5_approximate.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -O3 -o page_rank_gem5_approximate -DUSE_APPROXIMATE

clean:
	rm -rf *~ page_rank page_rank_gem5_normal page_rank_gem5_approximate
