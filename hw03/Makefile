CC = gcc
CFLAGS = 
LDFLAGS =

.SUFFIXES: .c .o
.c.o:
	$(CC) -c $(CFLAGS) $<
ALL = upper

all: $(ALL)

upper: upper.o
	$(CC) -o $@ $< $(LDFLAGS)

clean:
	rm -rf *.o $(ALL)
