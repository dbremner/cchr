TEXSOURCES := $(shell find -name '*.tex' -o -name '*.bib')

default: thesis.pdf

thesis.proc: $(TEXSOURCES)
	latex thesis.tex
	bibtex -terse thesis
	touch thesis.proc

thesis.pdf: thesis.proc
	pdflatex thesis.tex
	pdflatex thesis.tex

view: thesis.pdf
	kpdf thesis.pdf &

.PHONY: view
