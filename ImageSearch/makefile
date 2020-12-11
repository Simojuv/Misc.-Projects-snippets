IDIR =headers
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =lib

LIBS=-lexif

_OBJ = errorUtils.o formatUtils.o inputUtils.o myExifUtils.o myStructures.o searchUtils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: jpegsearch.out

jpegsearch.out: jpegsearch.o $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

$(ODIR)/jpegsearch.o: jpegsearch.c
	$(CC) -c $^ -o $@

$(ODIR)/%.o: $(IDIR)/%.c | obj
	$(CC) -c $^ -o $@

obj:
	mkdir -p $@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ -r obj
