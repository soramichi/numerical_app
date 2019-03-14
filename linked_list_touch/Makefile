gem5:
	gcc linked_list_touch_gem5_normal.c ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o linked_list_touch_gem5_normal -O3
	gcc linked_list_touch_gem5_approximate.c ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o linked_list_touch_gem5_approximate -O3 -DUSE_APPROXIMATE
	gcc linked_list_touch_gem5_approximate_prefetch.c ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o linked_list_touch_gem5_approximate_prefetch -O3 -DUSE_APPROXIMATE

clean:
	rm -rf *~ linked_list_touch linked_list_touch_bmalloc linked_list_touch_gem5_normal linked_list_touch_gem5_approximate linked_list_touch_gem5_approximate_prefetch

