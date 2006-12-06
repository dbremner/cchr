CC := gcc -Wall -pipe -std=c99

CFLAGS := -O3 -g0 -fomit-frame-pointer
LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common -Wl,--strip-all

all: bin fib fib.debug

clean:
	rm -f fib fib.debug fib.c

bin:
	ln -s ../bin bin

gcd.1: gcd.cchr
	bin/cchr gcd.cchr && $(CC) -x c $(CFLAGS) $(LDFLAGS) -o gcd.1 gcd.c

arcs.gcd: gcd.cchr
	bin/cchr gcd.cchr && $(CC) -fprofile-arcs -x c $(CFLAGS) $(LDFLAGS) -o arcs.gcd gcd.c

gcd.2: gcd.1 arcs.gcd
	./arcs.gcd 135 501000
	bin/cchr gcd.cchr && $(CC) -fbranch-probabilities -x c $(CFLAGS) $(LDFLAGS) -o gcd.2 gcd.c

fib.c: fib.cchr bin/cchr
	bin/cchr fib.cchr

fib.c.c: fib.c
	cpp <fib.c | egrep -v '^#' | indent -kr -l1024 >fib.c.c

fib_gmp.c: fib_gmp.cchr bin/cchr
	bin/cchr fib_gmp.cchr

fib: fib.c cchr_csm.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o fib fib.c

fib_gmp: fib_gmp.c cchr_csm.h
	$(CC) -lgmp $(CFLAGS) $(LDFLAGS) -o fib_gmp fib_gmp.c

fib.debug: fib.c cchr_csm.h
	$(CC) -DCSM_CONF_DEBUG -x c $(CFLAGS) $(LDFLAGS) -o fib.debug fib.c
