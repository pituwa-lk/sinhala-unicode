[ -f Makefile ] && make maintainer-clean
rm -rf aclocal.m4 config.guess config.h.in config.sub configure \
	config.rpath install-sh depcomp missing ltmain.sh mkinstalldirs \
	*~ autom*.cache/ debian/scim-sayura/ build-stamp \
	debian/scim-sayura.substvars debian/files config.status \
	configure-stamp debian/*.log
find -name 'Makefile.in' -exec rm {} \;
find -name 'Makefile' -exec rm {} \;
find -name '.libs' -prune -exec rm -rf {} \;
find -name '.deps' -prune -exec rm -rf {} \;

