
FONT=lklug
VERSION=0.6
DIST=ttf-sinhala-$(FONT)-$(VERSION)

all: ttf

ttf: $(FONT).ttf

$(FONT).ttf: $(FONT).sfd
	./convert.ff $(FONT)

install:
	install -m 755 -d $(DESTDIR)/usr/share/fonts/truetype/$(DIST)
	install -m 644 $(FONT).ttf $(DESTDIR)/usr/share/fonts/truetype/$(DIST)

clean:
	rm -f configure-stamp

distclean: clean
	rm -f $(DIST)-$(VERSION).tar.gz
	[ -x /usr/bin/fakeroot ] && fakeroot debian/rules clean

maintainer-clean: distclean
	rm -f $(FONT).ttf

dist: maintainer-clean all
	rm -rf $(DIST)
	mkdir -p $(DIST)
	cp -a convert.ff COPYING CREDITS $(FONT).ttf $(FONT).sfd Makefile README.fonts debian $(DIST)
	find $(DIST) -name CVS -prune -exec rm -rf "{}" \;
	tar -czf $(DIST).tar.gz $(DIST)
	rm -rf $(DIST)

