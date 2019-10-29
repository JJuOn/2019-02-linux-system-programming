CC = gcc
CFLAGS = 
LDFLAGS =

.SUFFIXES: .c .o
.c .o:
	$(CC) -c $(CFLAGS) $<

ALL = async

all: $(ALL)

async: async.o
	$(CC) -o $@ $< $(LDFLAGS)

clean:
	rm -rf *.o $(ALL)


