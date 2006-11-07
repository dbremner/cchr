CC := gcc -Wall -pipe -std=c99

CFLAGS := -m32 -O3 -ggdb3 -march=i686
LDFLAGS := -m32 -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common
OUTDIR := i686

#CFLAGS := m64 -O0 -ggdb3 -march=athlon64
#LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common
#OUTDIR := amd64-debug

#CFLAGS := -O3 -ggdb3 -march=athlon64 -m64
#LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common
#OUTDIR := amd64

$(OUTDIR)/cchr: $(OUTDIR)/parse.o $(OUTDIR)/main.o $(OUTDIR)/cchr.o $(OUTDIR)/model.o $(OUTDIR)/util.o
	$(CC) $(LDFLAGS) -o $(OUTDIR)/cchr $(OUTDIR)/parse.o $(OUTDIR)/cchr.o $(OUTDIR)/model.o $(OUTDIR)/util.o $(OUTDIR)/main.o

$(OUTDIR)/parse.o: parse.c *.h
	$(CC) $(CFLAGS) parse.c -c -o $(OUTDIR)/parse.o

$(OUTDIR)/main.o: main.c *.h
	$(CC) $(CFLAGS) main.c -c -o $(OUTDIR)/main.o

$(OUTDIR)/cchr.o: cchr.c *.h
	$(CC) $(CFLAGS) cchr.c -c -o $(OUTDIR)/cchr.o

$(OUTDIR)/util.o: util.c *.h
	$(CC) $(CFLAGS) util.c -c -o $(OUTDIR)/util.o

$(OUTDIR)/model.o: model.c *.h
	$(CC) $(CFLAGS) model.c -c -o $(OUTDIR)/model.o

$(OUTDIR)/gcd.cchr.bin: gcd.cchr.c model.c *.h
	$(CC) $(CFLAGS) gcd.cchr.c model.c -o $(OUTDIR)/gcd.cchr.bin

$(OUTDIR)/gcd.cchr.v1.bin: gcd.cchr.v1.c model.c *.h
	$(CC) $(CFLAGS) gcd.cchr.v1.c model.c -o $(OUTDIR)/gcd.cchr.v1.bin
	

$(OUTDIR)/gcd.csm.bin: gcd.csm.c *.h
	cpp -P <gcd.csm.c | indent -kr >gcd.csm.2.c
	$(CC) $(CFLAGS) gcd.csm.2.c -o $(OUTDIR)/gcd.csm.bin

$(OUTDIR)/gcd.v0.bin: gcd.v0.c
	$(CC) $(CFLAGS) gcd.v0.c -o $(OUTDIR)/gcd.v0.bin
