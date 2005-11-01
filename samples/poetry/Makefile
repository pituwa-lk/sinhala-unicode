
HTML = \
	aganthuka-sathkaraya.html \
	ashtaka.html \
	denipitiye-nugaruka.html \
	guththila.html \
	kotmale.html \
	salalihini.html \
	veli-thalapa.html \
	example.html

KAVI= ../../utils/kavi/kavi

all: kavi $(HTML)

kavi: $(KAVI)
	make -C ../../utils/kavi

%.html: %.txt
	$(KAVI) < $< > $@

clean:
	make -C ../../utils/kavi clean
	find . -name '*.html' -exec rm -f {} \;
	find . -name '*~' -exec rm -f {} \;

