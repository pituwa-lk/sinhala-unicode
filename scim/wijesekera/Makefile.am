SUBDIRS = intl po src data

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = config.rpath m4/ChangeLog

localedir = $(datadir)/locale
AM_CPPFLAGS = -I../intl -I$(top_srcdir)/intl -DLOCALEDIR=\"$(localedir)\"
LDADD = @LIBINTL@
