CC=gcc
CFLAGS=-w
LDFLAGS=-lpthread

.SUFFIXES:.c.o
.c.o:
	$(CC) -c $(CFLAGS) $<

ALL=tcps select

all: $(ALL)

tcps: tcps.o
	$(CC) -o $@ $< $(LDFLAGS)

select: select.o
	$(CC) -o $@ $< $(LDFLAGS)

clean:
	rm -rf *.o $(ALL)
