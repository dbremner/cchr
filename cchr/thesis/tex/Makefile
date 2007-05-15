TEXSOURCES := $(shell find -name '*.tex' -o -name '*.bib')
TEXOUT := out

default: $(TEXOUT)/thesis.pdf

$(TEXOUT)/thesis.proc: $(TEXSOURCES) $(TEXOUT)/THcover.pdf
	cd $(TEXOUT); export TEXINPUTS=.:..:; pdflatex thesis.tex; bibtex -terse thesis; touch thesis.proc; cd ..

$(TEXOUT)/THcover.pdf: THcover.tex
	cd $(TEXOUT); export TEXINPUTS=.:..:; latex THcover.tex; dvipdf THcover.dvi; cd ..

clean:
	cd $(TEXOUT); rm -f *.aux *.bbl *.blg *.dvi *.lof *.log *.lot *.out *.pdf *.proc *.toc; cd ..

$(TEXOUT)/thesis.pdf: $(TEXOUT)/thesis.proc
	cd $(TEXOUT); export TEXINPUTS=.:..:; pdflatex thesis.tex; pdflatex thesis.tex; cd ..

view: $(TEXOUT)/thesis.pdf
	kpdf $(TEXOUT)/thesis.pdf &

upload: ~/mnt/ulyssis/www/thesis.pdf

~/mnt/ulyssis/www/thesis.pdf: $(TEXOUT)/thesis.pdf
	if [ -d ~/mnt/ulyssis/www ]; then cp -f $(TEXOUT)/thesis.pdf ~/mnt/ulyssis/www/thesis.pdf; fi

.PHONY: view upload
