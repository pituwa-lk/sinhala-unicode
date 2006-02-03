AM_CPPFLAGS = \
	-DSCIM_SINHALA_LOCALEDIR=\"$(datadir)/locale\" \
	-DSCIM_ICONDIR=\"@SCIM_ICONDIR@\"

INCLUDE	= \
	-I$(top_builddir) \
	-I$(top_srcdir) \
	-I$(top_srcdir)/src

noinst_HEADERS = \
	intl.h \
	scim_sinhala_imengine_factory.h \
	scim_sinhala_imengine.h

moduledir = @SCIM_MODULEDIR@/IMEngine
module_LTLIBRARIES = sinhala.la

sinhala_la_SOURCES = \
	scim_sinhala_action.h \
	scim_sinhala_action.cpp \
	scim_sinhala_imengine_factory.cpp \
	scim_sinhala_imengine.cpp

sinhala_la_CFLAGS = @SCIM_CFLAGS@ -I/usr/include/scim-1.0/
sinhala_la_CXXFLAGS = @SCIM_CFLAGS@ -I/usr/include/scim-1.0/

sinhala_la_LDFLAGS = \
	-avoid-version \
	-rpath $(moduledir) \
	-module \
	@SCIM_LIBS@

