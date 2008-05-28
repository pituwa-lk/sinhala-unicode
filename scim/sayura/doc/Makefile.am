TEX= sayura

EXTRA_DIST = index.html sayura.tex sayura.pdf sinhala.sty style.css

pdf: $(TEX).pdf

$(TEX).pdf: $(TEX).tex
	if test ! -f $(TEX).aux  ; then \
	    xelatex $(TEX).tex; \
	fi;
	xelatex $(TEX).tex

clean:
	rm -f $(TEX).log $(TEX).aux $(TEX).toc *~ sayura.synctex.gz

distclean: clean

maintainer-clean: distclean
	rm -f $(TEX).pdf
	rm -f Makefile

