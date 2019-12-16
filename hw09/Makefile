CC = gcc
CFLAGS = -w
LDFLAGS = -lpthread

.SUFFIXES: .c .o
.c .o:
	$(CC) -c $(CFLAGS) $<

ALL = sipc1_s sipc2_s sipc_t_mutexcond sipc_t_sem

all: $(ALL)

semlib.o: semlib.c
	$(CC) -c $< $(LDFLAGS)

sipc1_s: sipc1_s.o semlib.o
	$(CC) -o $@ sipc1_s.o semlib.o $(LDFLAGS)

sipc2_s: sipc2_s.o semlib.o
	$(CC) -o $@ sipc2_s.o semlib.o $(LDFLAGS)

sipc_t_mutexcond: sipc_t_mutexcond.o
	$(CC) -o $@ $< $(LDFLAGS)

sipc_t_sem: sipc_t_sem.o
	$(CC) -o $@ $< $(LDFLAGS)

clean:
	rm -rf *.o $(ALL)


