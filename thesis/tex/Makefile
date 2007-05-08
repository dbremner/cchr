TEXSOURCES := $(shell find -name '*.tex' -o -name '*.bib')
TEXOUT := out

default: $(TEXOUT)/book.pdf

$(TEXOUT)/thesis.proc: $(TEXSOURCES)
	cd $(TEXOUT); export TEXINPUTS=.:..:; latex thesis.tex; bibtex -terse thesis; touch thesis.proc; cd ..

$(TEXOUT)/THcover.pdf: THcover.tex
	cd $(TEXOUT); export TEXINPUTS=.:..:; latex THcover.tex; dvipdf THcover.dvi; cd ..

clean:
	cd $(TEXOUT); rm -f *.aux *.bbl *.blg *.dvi *.lof *.log *.lot *.out *.pdf *.proc *.toc; cd ..

$(TEXOUT)/thesis.pdf: $(TEXOUT)/thesis.proc
	cd $(TEXOUT); export TEXINPUTS=.:..:; pdflatex thesis.tex; pdflatex thesis.tex; cd ..

$(TEXOUT)/book.pdf: $(TEXOUT)/thesis.proc $(TEXOUT)/THcover.pdf
	cd $(TEXOUT); pdfjoin --paper a4paper --outfile book.pdf THcover.pdf thesis.pdf; cd ..

view: $(TEXOUT)/book.pdf
	kpdf $(TEXOUT)/book.pdf &

upload: ~/mnt/ulyssis/www/thesis.pdf

~/mnt/ulyssis/www/thesis.pdf: $(TEXOUT)/book.pdf
	if [ -d ~/mnt/ulyssis/www ]; then cp -f $(TEXOUT)/book.pdf ~/mnt/ulyssis/www/thesis.pdf; fi

.PHONY: view upload
