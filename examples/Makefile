CC := gcc -Wall -pipe -std=c99

MODE := efence

ifeq ($(MODE),debug)
  CFLAGS := -O0 -ggdb3
  LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common
else
  ifeq ($(MODE),efence)
    CFLAGS := -O0 -ggdb3 -DUSE_EFENCE
    LDFLAGS := -lefence -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common
  else
    CFLAGS := -O3 -g0 -fomit-frame-pointer -march=athlon64 -frename-registers -ftracer -fweb
    LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common -Wl,--strip-all
  endif
endif

all: bin fib fib.debug

clean:
	rm -f fib fib.debug fib.c

bin:
	ln -s ../bin bin

gcd.c: gcd.cchr bin/cchr Makefile
	bin/cchr gcd.cchr

gcd: gcd.c cchr_csm.h Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o gcd gcd.c

gcd.p: gcd.c cchr_csm.h Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -fprofile-generate -o gcd.a gcd.c
	time ./gcd.a 50000000 5 >/dev/null
	$(CC) $(CFLAGS) $(LDFLAGS) -fprofile-use -o gcd.p gcd.c

primes.c: primes.cchr bin/cchr Makefile
	bin/cchr primes.cchr

primes: primes.c cchr_csm.h Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o primes primes.c

primes.p: primes.c cchr_csm.h Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -fprofile-generate -o primes.a primes.c
	time ./primes.a 5000 5 >/dev/null
	$(CC) $(CFLAGS) $(LDFLAGS) -fprofile-use -o primes.p primes.c

fib.c: fib.cchr bin/cchr Makefile
	bin/cchr fib.cchr

fib.c.debug: fib.c cchr_csm.h Makefile
	cpp -DCSM_CONF_DEBUG <fib.c | egrep -v '^#' | indent -kr -l1024 >fib.c.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o fib.c.debug fib.c.c

fib_gmp.c: fib_gmp.cchr bin/cchr Makefile
	bin/cchr fib_gmp.cchr

fib: fib.c cchr_csm.h Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -o fib fib.c

fib_gmp: fib_gmp.c cchr_csm.h Makefile
	$(CC) -lgmp $(CFLAGS) $(LDFLAGS) -o fib_gmp fib_gmp.c

fib_gmp.p: fib_gmp.c cchr_csm.h Makefile
	$(CC) -lgmp $(CFLAGS) $(LDFLAGS) -fprofile-generate -o fib_gmp.a fib_gmp.c
	time ./fib_gmp.a 3000 >/dev/null
	$(CC) -lgmp $(CFLAGS) $(LDFLAGS) -fprofile-use -o fib_gmp.p fib_gmp.c

fib.debug: fib.c cchr_csm.h Makefile
	$(CC) -DCSM_CONF_DEBUG $(CFLAGS) $(LDFLAGS) -o fib.debug fib.c

logtest: logtest.c ../logical.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o logtest logtest.c
