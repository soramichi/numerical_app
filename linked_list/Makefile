all:
	gcc linked_list.c -o linked_list -O3
	gcc linked_list_bmalloc.c -o linked_list_bmalloc -O3 -DIMP -lnuma -pthread

debug:
	gcc linked_list.c -o linked_list -O3 -DDEBUG
	gcc linked_list_bmalloc.c -o linked_list_bmalloc -O3 -DDEBUG -DIMP -lnuma -pthread

clean:
	rm -rf *~ linked_list linked_list_bmalloc
