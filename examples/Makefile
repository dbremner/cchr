CC := gcc -Wall -pipe -std=c99

CFLAGS := -O3 -g0 -fomit-frame-pointer
LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common -Wl,--strip-all

all: bin gcd fib

clean:
	rm -f fib gcd

bin:
	ln -s ../bin bin

gcd: gcd.c
	bin/cchr <gcd.c | $(CC) -x c $(CFLAGS) $(LDFLAGS) -o gcd -

fib: fib.c
	bin/cchr <fib.c | $(CC) -x c $(CFLAGS) $(LDFLAGS) -o fib -

