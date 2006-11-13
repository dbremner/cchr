CC := gcc -Wall -pipe -std=c99
INTDIR := intermediate/

#CFLAGS := -m32 -O3 -g0
#LDFLAGS := -m32 -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common -Wl,--strip-all
#OUTDIR := i686

#CFLAGS := -m64 -O0 -ggdb3 -march=athlon64
#LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common
#OUTDIR := amd64-debug

CFLAGS := -O3 -g0 -march=athlon64 -pipe -fweb -frename-registers -ftracer -fpeel-loops
LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common -Wl,--strip-all
OUTDIR := amd64

$(INTDIR)/cchr.tab.c $(INTDIR)/cchr.tab.h: cchr.y
	bison -dv -o $(INTDIR)/cchr.tab.c cchr.y

$(INTDIR)/cchr.lex.c: $(INTDIR)/cchr.tab.h cchr.lex
	flex -o $(INTDIR)/cchr.lex.c cchr.lex

$(OUTDIR)/cchr.tab.o: $(INTDIR)/cchr.tab.c parsestr.h
	$(CC) $(CFLAGS) -I . $(INTDIR)/cchr.tab.c -c -o $(OUTDIR)/cchr.tab.o

$(OUTDIR)/cchr.lex.o: $(INTDIR)/cchr.tab.h $(INTDIR)/cchr.lex.c parsestr.h
	$(CC) $(CFLAGS) -I . $(INTDIR)/cchr.lex.c -c -o $(OUTDIR)/cchr.lex.o

$(OUTDIR)/cchr.parse: $(OUTDIR)/cchr.tab.o $(OUTDIR)/cchr.lex.o
	$(CC) $(LDFLAGS) -o $(OUTDIR)/cchr.parse $(OUTDIR)/cchr.tab.o $(OUTDIR)/cchr.lex.o

