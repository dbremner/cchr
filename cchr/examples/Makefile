CC := gcc -Wall -pipe -std=c99

CFLAGS := -O3 -g0 -fomit-frame-pointer
LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common -Wl,--strip-all

all: bin gcd.1 gcd.2 fib

clean:
	rm -f fib gcd.1 arcs.gcd gcd.2

bin:
	ln -s ../bin bin

gcd.1: gcd.cchr
	bin/cchr gcd.cchr
	$(CC) -x c $(CFLAGS) $(LDFLAGS) -o gcd.1 gcd.c

arcs.gcd: gcd.cchr
	bin/cchr gcd.cchr
	$(CC) -fprofile-arcs -x c $(CFLAGS) $(LDFLAGS) -o arcs.gcd gcd.c

gcd.2: gcd.1 arcs.gcd
	./arcs.gcd 5 1234567890
	bin/cchr gcd.cchr
	$(CC) -fbranch-probabilities -x c $(CFLAGS) $(LDFLAGS) -o gcd.2 gcd.c

fib: fib.cchr
	bin/cchr fib.cchr
	$(CC) -x c $(CFLAGS) $(LDFLAGS) -o fib fib.c
