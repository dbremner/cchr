CC := gcc

CFLAGS := -std=c99 -m64 -O0 -ggdb3 -Wall -march=athlon64 -save-temps
LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common
OUTDIR := amd64-debug

#CFLAGS := -std=c99 -m64 -O3 -g0 -Wall -march=athlon64 -pipe
#LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common -Wl,--strip-all
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

