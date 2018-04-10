all:
	gcc -O3 gemv.c -o gemv
	gcc -O3 gemv_block.c -o gemv_block
#	gcc -O3 gemm_block_bmalloc.c -o gemm_block_bmalloc -DIMP -lnuma -pthread

debug:
	gcc -O3 gemv.c -o gemv -DDEBUG
	gcc -O3 gemv_block.c -o gemv_block -DDEBUG

clean:
	rm -f gemv gemv_block gemv_block_bmalloc *~

