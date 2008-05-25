TEX= sayura

EXTRA_DIST = index.html sayura.tex sinhala.sty style.css

pdf: $(TEX).pdf

$(TEX).pdf: $(TEX).tex
	if test ! -f $(TEX).aux  ; then \
	    xelatex $(TEX).tex; \
	fi;
	xelatex $(TEX).tex

clean:
	rm -f $(TEX).pdf $(TEX).log $(TEX).aux $(TEX).toc *~ sayura.synctex.gz
