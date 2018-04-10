all:
	make vanilla
	make bmalloc

debug:
	make vanilla_debug
	make bmalloc_debug

vanilla:
	gcc -O3 seq_search.c -o seq_search

bmalloc:
	gcc -O3 seq_search_bmalloc.c -o seq_search_bmalloc -DIMP -pthread -lnuma

vanilla_debug:
	gcc -O3 seq_search.c -o seq_search -DDEBUG

bmalloc_debug:
	gcc -O3 seq_search_bmalloc.c -o seq_search_bmalloc -DIMP -pthread -lnuma

clean:
	rm -rf *~ seq_search seq_search_bmalloc
