
FONT=lklug
VERSION=0.5.0
DIST=ttf-sinhala-$(FONT)

all: $(FONT).ttf

$(FONT).ttf: $(FONT).sfd
	./convert.ff $(FONT)

clean:
	rm -f $(FONT).ttf *stamp

distclean: clean
	rm -rf *stamp debian/ttf-sinhala-lklug debian/files debian/tmp debian/*.log

dist:
	rm -rf $(DIST)
	mkdir -p $(DIST)
	cp -a convert.ff CREDITS debian lklug.sfd Makefile README.fonts $(DIST)
	tar -czf $(DIST)-$(VERSION).tar.gz $(DIST)
	rm -rf $(DIST)

