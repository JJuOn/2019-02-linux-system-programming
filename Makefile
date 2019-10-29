CC = gcc
CFLAGS = 
LDFLAGS =

.SUFFIXES: .c .o
.c .o:
	$(CC) -c $(CFLAGS) $<

ALL = 

all: $(ALL)


clean:
	rm -rf *.o $(ALL)


