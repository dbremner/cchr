CC := gcc -Wall -pipe -std=c99

#MODE := efence

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

gcd.1: gcd.cchr Makefile
	bin/cchr gcd.cchr && $(CC) -x c $(CFLAGS) $(LDFLAGS) -o gcd.1 gcd.c

arcs.gcd: gcd.cchr Makefile
	bin/cchr gcd.cchr && $(CC) -fprofile-arcs -x c $(CFLAGS) $(LDFLAGS) -o arcs.gcd gcd.c

gcd.2: gcd.1 arcs.gcd Makefile
	./arcs.gcd 135 501000
	bin/cchr gcd.cchr && $(CC) -fbranch-probabilities -x c $(CFLAGS) $(LDFLAGS) -o gcd.2 gcd.c

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
