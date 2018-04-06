all:
	gcc -O3 gemm.c -o gemm
	gcc -O3 gemm_block.c -o gemm_block
	gcc -O3 gemm_block_bmalloc.c -o gemm_block_bmalloc -DIMP -lnuma -pthread

debug:
	gcc -O3 gemm.c -o gemm -DDEBUG
	gcc -O3 gemm_block.c -o gemm_block -DDEBUG

clean:
	rm -f gemm gemm_block gemm_block_bmalloc *~

