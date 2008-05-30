
FONT=lklug
VERSION=0.5.1
DIST=ttf-sinhala-$(FONT)

all: $(FONT).ttf

$(FONT).ttf: $(FONT).sfd
	./convert.ff $(FONT)

install:
	install -m 755 -d $(DESTDIR)/usr/share/fonts/truetype/sinhala
	install -m 644 lklug.ttf $(DESTDIR)/usr/share/fonts/truetype/sinhala

clean:
	rm -f $(FONT).ttf
	rm -f configure-stamp

distclean: clean
	rm -f $(DIST)-$(VERSION).tar.gz
	[ -x /usr/bin/fakeroot ] && fakeroot debian/rules clean

dist: distclean
	rm -rf $(DIST)
	mkdir -p $(DIST)
	cp -a convert.ff CREDITS lklug.sfd Makefile README.fonts debian $(DIST)
	find $(DIST) -name CVS -prune -exec rm -rf "{}" \;
	tar -czf $(DIST)-$(VERSION).tar.gz $(DIST)
	rm -rf $(DIST)

