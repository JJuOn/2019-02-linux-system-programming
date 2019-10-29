CC = gcc
CFLAGS = 
LDFLAGS = 

.SUFFIXES : .c.o

.c.o:
	$(CC) -c $(CFLAGS) $<

ALL = mylsl

all: $(ALL)

mylsl: mylsl.o
	$(CC) -o $@ $< $(LDFLAGS)

clean:
	rm -rf *o $(ALL)
