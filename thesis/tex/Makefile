TEXSOURCES := $(shell find -name '*.tex' -o -name '*.bib')
TEXOUT := out

default: $(TEXOUT)/thesis.pdf

$(TEXOUT)/thesis.proc: $(TEXSOURCES)
	cd $(TEXOUT); export TEXINPUTS=.:..:; latex thesis.tex; bibtex -terse thesis; touch thesis.proc; cd ..

clean:
	cd $(TEXOUT); rm -f *.aux *.bbl *.blg *.dvi *.lof *.log *.lot *.out *.pdf *.proc *.toc; cd ..

$(TEXOUT)/thesis.pdf: $(TEXOUT)/thesis.proc
	cd $(TEXOUT); export TEXINPUTS=.:..:; pdflatex thesis.tex; pdflatex thesis.tex; cd ..

view: $(TEXOUT)/thesis.pdf
	kpdf $(TEXOUT)/thesis.pdf &

upload: ~/mnt/ulyssis/www/thesis.pdf

~/mnt/ulyssis/www/thesis.pdf: $(TEXOUT)/thesis.pdf
	if [ -d ~/mnt/ulyssis/www ]; then cp -f $(TEXOUT)/thesis.pdf ~/mnt/ulyssis/www; fi

.PHONY: view upload

