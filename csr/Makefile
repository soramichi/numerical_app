all:
	gcc dense_to_csr.c -o dense_to_csr -O3
	gcc csr_mm.c -o csr_mm -O3
	gcc csr_mm_bmalloc.c -o csr_mm_bmalloc -O3 -DIMP -lnuma -pthread

debug:
	gcc csr_mm.c -o csr_mm -Wall -DDEBUG -g

clean:
	rm -rf *~ dense_to_csr csr_mm csr_mm_bmalloc
