TEXSOURCES := $(shell find -name '*.tex' -o -name '*.bib')
TEXOUT := out

default: thesis.pdf

thesis.proc: $(TEXSOURCES)
	cd $(TEXOUT); export TEXINPUTS=.:..:; latex thesis.tex; bibtex -terse thesis; touch thesis.proc; cd ..

clean:
	cd $(TEXOUT); rm -f *.aux *.bbl *.blg *.dvi *.lof *.log *.lot *.out *.pdf *.proc *.toc; cd ..

thesis.pdf: thesis.proc
	cd $(TEXOUT); export TEXINPUTS=.:..:; pdflatex thesis.tex; pdflatex thesis.tex; cd ..

view: thesis.pdf
	kpdf $(TEXOUT)/thesis.pdf &

.PHONY: view
