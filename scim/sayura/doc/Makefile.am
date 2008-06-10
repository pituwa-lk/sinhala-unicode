DOC= sayura.pdf sayura-paper.pdf

EXTRA_DIST = index.html sayura.tex sayura.pdf sinhala.sty style.css

all: $(DOC)

%.pdf: %.tex
	if test ! -f $(basename $<).aux  ; then \
	    xelatex $<; \
	fi;
	xelatex $<

clean:
	rm -f *.log *.aux *.toc *~ sayura.synctex.gz

distclean: clean

maintainer-clean: distclean
	rm -f $(DOC)
	rm -f Makefile Makefile.in

