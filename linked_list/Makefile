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

clean:
	rm -rf *~ linked_list linked_list_bmalloc
