
HTML = \
	ashtaka.html \
	guththila.html \
	kotmale.html \
	salalihini.html

KAVI= ../../utils/kavi/kavi

all: kavi $(HTML)

kavi: $(KAVI)
	make -C ../../utils/kavi

%.html: %.txt
	$(KAVI) < $< > $@

clean:
	make -C ../../utils/kavi clean
	rm -f *.html *~

