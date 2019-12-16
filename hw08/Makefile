CC = gcc
CFLAGS = -w
LDFLAGS =

.SUFFIXES: .c .o
.c .o:
	$(CC) -c $(CFLAGS) $<

ALL = pipe mipc

all: $(ALL)

pipe: pipe.o
	$(CC) -o $@ $< $(LDFLAGS)
mipc: mipc.o synclib.o
	$(CC) -o $@ mipc.o synclib.o $(LDFLAGS)

clean:
	rm -rf *.o $(ALL)


