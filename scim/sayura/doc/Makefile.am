TEX= sayura

pdf: $(TEX).pdf

$(TEX).pdf: $(TEX).tex
	if test ! -f $(TEX).aux  ; then \
	    xelatex $(TEX).tex; \
	fi;
	xelatex $(TEX).tex

clean:
	rm -f $(TEX).pdf $(TEX).log $(TEX).aux $(TEX).toc *~ sayura.synctex.gz
