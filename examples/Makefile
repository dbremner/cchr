CC := gcc -Wall -pipe -std=c99

CFLAGS := -O3 -g0 -fomit-frame-pointer
LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common -Wl,--strip-all

all: bin gcd.1 gcd.2 fib

clean:
	rm -f fib gcd

bin:
	ln -s ../bin bin

gcd.1: gcd.c
	bin/cchr gcd.c
	$(CC) -x c $(CFLAGS) $(LDFLAGS) -o gcd.1 gcd.c.c

arcs.gcd: gcd.c
	bin/cchr gcd.c
	$(CC) -fprofile-arcs -x c $(CFLAGS) $(LDFLAGS) -o arcs.gcd gcd.c.c

gcd.2: gcd.1 arcs.gcd
	time ./arcs.gcd 5 1234567890
	bin/cchr gcd.c
	$(CC) -fbranch-probabilities -x c $(CFLAGS) $(LDFLAGS) -o gcd.2 gcd.c.c

fib: fib.c
	bin/cchr fib.c
	$(CC) -x c $(CFLAGS) $(LDFLAGS) -o fib fib.c.c

