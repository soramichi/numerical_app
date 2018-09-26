all:
	make vanilla
	make bmalloc

debug:
	make vanilla_debug
	make bmalloc_debug

vanilla:
	gcc linked_list.c -o linked_list -O3 -g

bmalloc:
	gcc linked_list_bmalloc.c -o linked_list_bmalloc -O3 -DIMP -lnuma -pthread

vanilla_debug:
	gcc linked_list.c -o linked_list -O3 -DDEBUG

vanilla_bmalloc:
	gcc linked_list_bmalloc.c -o linked_list_bmalloc -O3 -DDEBUG -DIMP -lnuma -pthread

gem5:
	gcc linked_list_gem5_normal.c ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o linked_list_gem5_normal -O3
	gcc linked_list_gem5_approximate.c ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o linked_list_gem5_approximate -O3 -DUSE_APPROXIMATE

clean:
	rm -rf *~ linked_list linked_list_bmalloc linked_list_gem5_normal linked_list_gem5_approximate
