CC = gcc
CFLAGS = 
LDFLAGS =

.SUFFIXES: .c .o
.c .o:
	$(CC) -c $(CFLAGS) $<

ALL = show upper count myrm size

all: $(ALL)

show: show.o
	$(CC) -o $@ $< $(LDFLAGS)

upper: upper.o
	$(CC) -o $@ $< $(LDFLAGS)

count: count.o
	$(CC) -o $@ $< $(LDFLAGS)

myrm: myrm.o
	$(CC) -o $@ $< $(LDFLAGS)

size: size.o
	$(CC) -o $@ $< $(LDFLAGS)


clean:
	rm -rf *.o $(ALL)


