all: JPEGSearch.out

JPEGSearch.out: JPEGSearch.o
	gcc -o JPEGSearch.out JPEGSearch.o -lexif

JPEGSearch.o: JPEGSearch.C
	gcc -c JPEGSearch.c -lexif

clean:
	rm JPEGSearch.o JPEGSearch.out
