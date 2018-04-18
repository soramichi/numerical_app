all:
	gcc dense_to_csr.c -o dense_to_csr -O3
	gcc spmv.c -o spmv -O3
	gcc spmv_bmalloc.c -o spmv_bmalloc -O3 -DIMP -lnuma -pthread

debug:
	gcc spmv.c -o spmv -Wall -DDEBUG -g

clean:
	rm -rf *~ dense_to_csr spmv spmv_bmalloc
