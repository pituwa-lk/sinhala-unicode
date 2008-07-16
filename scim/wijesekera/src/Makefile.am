AM_CPPFLAGS = \
	-DSCIM_WIJESEKERA_LOCALEDIR=\"$(datadir)/locale\" \
	-DSCIM_ICONDIR=\"@SCIM_ICONDIR@\"
INCLUDE	= \
	-I$(top_builddir) \
	-I$(top_srcdir) \
	-I$(top_srcdir)/src 

noinst_HEADERS = \
	intl.h \
	scim_wijesekera_imengine_factory.h \
	scim_wijesekera_imengine.h \
	scim_wijesekera_prefs.h	\
	parser.h compat_data.h states.h complex_def.h layout.h imcompat.h

moduledir = @SCIM_MODULEDIR@/IMEngine
module_LTLIBRARIES = wijesekera.la

wijesekera_la_SOURCES = \
	scim_wijesekera_imengine_factory.cpp \
	scim_wijesekera_imengine.cpp	\
	parser.cpp wijesekera.cpp imcompat.cpp

wijesekera_la_CFLAGS = @SCIM_CFLAGS@  @SCIM_DEBUG_FLAGS@
wijesekera_la_CXXFLAGS = @SCIM_CFLAGS@ @SCIM_DEBUG_FLAGS@

wijesekera_la_LDFLAGS = \
	-avoid-version \
	-rpath $(moduledir) \
	-module \
	@LIBTOOL_EXPORT_OPTIONS@ \
	@SCIM_LIBS@

