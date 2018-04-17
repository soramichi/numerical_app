all:
	gcc dense_to_csr.c -o dense_to_csr -Wall
	gcc csr_mm.c -o csr_mm -Wall

debug:
	gcc csr_mm.c -o csr_mm -Wall -DDEBUG

clean:
	rm -rf *~ dense_to_csr csr_mm
