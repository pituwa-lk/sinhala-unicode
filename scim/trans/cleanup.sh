[ -f Makefile ] && make distclean
rm -rf aclocal.m4 config.guess config.h.in config.sub configure \
	config.rpath install-sh depcomp missing ltmain.sh mkinstalldirs \
	*~ autom*.cache/ debian/scim-sinhala-trans/ build-stamp \
	debian/scim-sinhala-trans.substvars debian/files config.status
find -name 'Makefile.in' -exec rm {} \;
find -name 'Makefile' -exec rm {} \;
find -name '.libs' -prune -exec rm -rf {} \;
find -name '.deps' -prune -exec rm -rf {} \;
