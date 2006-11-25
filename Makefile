CC := gcc -Wall -pipe -std=c99
INTDIR := intermediate

#CFLAGS := -O3 -g0
#LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common
#OUTDIR := bin

CFLAGS := -O0 -ggdb3 -march=athlon64
LDFLAGS := -Wl,-O2 -Wl,--enable-new-dtags -Wl,--sort-common
OUTDIR := debug

all: $(INTDIR) $(OUTDIR) $(OUTDIR)/cchr.parse

$(OUTDIR):
	mkdir $(OUTDIR)

$(INTDIR):
	mkdir $(INTDIR)

clean: 
	rm -rf $(INTDIR)/* $(OUTDIR)/*

$(OUTDIR)/cchr.parse: $(OUTDIR)/cchr.tab.o $(OUTDIR)/cchr.lex.o $(OUTDIR)/abs2sem.o $(OUTDIR)/main.o $(OUTDIR)/sem2csm.o
	$(CC) $(LDFLAGS) -o $(OUTDIR)/cchr.parse $(OUTDIR)/cchr.tab.o $(OUTDIR)/cchr.lex.o $(OUTDIR)/abs2sem.o $(OUTDIR)/sem2csm.o $(OUTDIR)/main.o

$(INTDIR)/cchr.tab.c $(INTDIR)/cchr.tab.h: cchr.y
	bison -dv -o $(INTDIR)/cchr.tab.c cchr.y

$(INTDIR)/cchr.lex.c: $(INTDIR)/cchr.tab.h cchr.lex
	flex -o $(INTDIR)/cchr.lex.c cchr.lex

$(OUTDIR)/cchr.tab.o: $(INTDIR)/cchr.tab.c parsestr.h alist.h
	$(CC) $(CFLAGS) -I . $(INTDIR)/cchr.tab.c -c -o $(OUTDIR)/cchr.tab.o

$(OUTDIR)/cchr.lex.o: $(INTDIR)/cchr.tab.h $(INTDIR)/cchr.lex.c parsestr.h
	$(CC) $(CFLAGS) -I . $(INTDIR)/cchr.lex.c -c -o $(OUTDIR)/cchr.lex.o

$(OUTDIR)/abs2sem.o: abs2sem.c semtree.h parsestr.h abs2sem.h alist.h
	$(CC) $(CFLAGS) abs2sem.c -c -o $(OUTDIR)/abs2sem.o

$(OUTDIR)/sem2csm.o: sem2csm.c semtree.h sem2csm.h alist.h
	$(CC) $(CFLAGS) sem2csm.c -c -o $(OUTDIR)/sem2csm.o

$(OUTDIR)/main.o: main.c sem2csm.h abs2sem.h semtree.h parsestr.h alist.h
	$(CC) $(CFLAGS) main.c -c -o $(OUTDIR)/main.o
