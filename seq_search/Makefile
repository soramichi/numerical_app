all:
	make vanilla

debug:
	make vanilla_debug

vanilla:
	gcc -O3 seq_search.c -o seq_search

vanilla_debug:
	gcc -O3 seq_search.c -o seq_search -DDEBUG

clean:
	rm -rf *~ seq_search
