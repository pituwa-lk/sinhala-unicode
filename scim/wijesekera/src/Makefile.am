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
	scim_wijesekera_prefs.h

moduledir = @SCIM_MODULEDIR@/IMEngine
module_LTLIBRARIES = wijesekera.la

wijesekera_la_SOURCES = \
	scim_wijesekera_imengine_factory.cpp \
	scim_wijesekera_imengine.cpp

wijesekera_la_CFLAGS = @SCIM_CFLAGS@  @SCIM_DEBUG_FLAGS@
wijesekera_la_CXXFLAGS = @SCIM_CFLAGS@ @SCIM_DEBUG_FLAGS@

wijesekera_la_LDFLAGS = \
	-avoid-version \
	-rpath $(moduledir) \
	-module \
	@LIBTOOL_EXPORT_OPTIONS@ \
	@SCIM_LIBS@

if SCIM_BUILD_SETUP
SETUP_MODULE = wijesekera-imengine-setup.la
endif

setupmoduledir           = @SCIM_MODULEDIR@/SetupUI
setupmodule_LTLIBRARIES  = $(SETUP_MODULE)

wijesekera_imengine_setup_la_SOURCES = scim_wijesekera_imengine_setup.cpp

wijesekera_imengine_setup_la_CFLAGS  = @SCIM_GTKUTILS_CFLAGS@ @SCIM_CFLAGS@ @SCIM_DEBUG_FLAGS@

wijesekera_imengine_setup_la_CXXFLAGS= @SCIM_GTKUTILS_CFLAGS@ @SCIM_CFLAGS@ @SCIM_DEBUG_FLAGS@

wijesekera_imengine_setup_la_LDFLAGS = -avoid-version \
				-rpath $(setupmoduledir) \
				-module \
				@LIBTOOL_EXPORT_OPTIONS@ \
				@SCIM_GTKUTILS_LIBS@ \
				@LTLIBINTL@ \
				@SCIM_LIBS@
