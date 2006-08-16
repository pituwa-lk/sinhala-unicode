make distclean # ignore this error
rm -rf aclocal.m4 config.guess config.h.in config.sub configure \
	config.rpath install-sh depcomp missing ltmain.sh mkinstalldirs \
	*~ autom*.cache/ debian/scim-sinhala-trans/ build-stamp \
	debian/scim-sinhala-trans.substvars debian/files config.status
cp intl/Makefile.in intl/Makefile.in.dj
find -name 'Makefile.in' -exec rm {} \;
mv intl/Makefile.in.dj intl/Makefile.in
find -name 'Makefile' -exec rm {} \;
find -name '.libs' -prune -exec rm -rf {} \;
find -name '.deps' -prune -exec rm -rf {} \;
rm -f config.h config.log stamp-h1 libtool
rm -f po/si.gmo po/stamp-po po/scim-imengine-wijesekera.pot
