all:
	gcc dense_to_csr.c -o dense_to_csr -O3 -Wall
	gcc csr_mm.c -o csr_mm -O3 -Wall

debug:
	gcc csr_mm.c -o csr_mm -Wall -DDEBUG -g

clean:
	rm -rf *~ dense_to_csr csr_mm
