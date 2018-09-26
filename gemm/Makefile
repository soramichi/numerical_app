all:
	gcc -O3 gemm.c -o gemm
	gcc -O3 gemm_block.c -o gemm_block
	gcc -O3 gemm_block_bmalloc.c -o gemm_block_bmalloc -DIMP -lnuma -pthread

debug:
	gcc -O3 gemm.c -o gemm -DDEBUG
	gcc -O3 gemm_block.c -o gemm_block -DDEBUG

gem5:
	gcc -O3 gemm_block_gem5_normal.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o gemm_block_gem5_normal
	gcc -O3 gemm_block_gem5_approximate.c  ../../mmap_allocator/mmap_allocator.c -I ../../mmap_allocator -o gemm_block_gem5_approximate -DUSE_APPROXIMATE

clean:
	rm -f gemm gemm_block gemm_block_bmalloc gemm_block_gem5_normal gemm_block_gem5_approximate *~

