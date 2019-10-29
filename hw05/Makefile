CC=gcc
CFLAGS=
LDFLAGS=-lpthread

.SUFFIXES: .c.o

.c.o:
	$(CC) -c $(CFLAGS) $<

ALL=mysystem tadd

all: $(ALL)

mysystem: mysystem.o
	$(CC) -o $@ $< $(LDFLAGS)

tadd: tadd.o
	$(CC) -o $@ $< $(LDFLAGS)

clean:
	rm -rf $(ALL) *.o
