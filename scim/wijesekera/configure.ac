#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([scim-wijesekera],[0.3.4],[nidujay *killspam* gmail dot com])
AC_CONFIG_SRCDIR([src/scim_wijesekera_prefs.h])

# Save this value here, since automake will set cflags and cxxflags later
cflags_set=${CFLAGS+set}
cppflags_set=${CPPFLAGS+set}

SCIM_WIJESEKERA_MAJOR_VERSION=0
SCIM_WIJESEKERA_MINOR_VERSION=3
SCIM_WIJESEKERA_MICRO_VERSION=4

SCIM_WIJESEKERA_VERSION=$SCIM_WIJESEKERA_MAJOR_VERSION.$SCIM_WIJESEKERA_MINOR_VERSION.$SCIM_WIJESEKERA_MICRO_VERSION

AC_SUBST(SCIM_WIJESEKERA_MAJOR_VERSION)
AC_SUBST(SCIM_WIJESEKERA_MINOR_VERSION)
AC_SUBST(SCIM_WIJESEKERA_MICRO_VERSION)
AC_SUBST(SCIM_WIJESEKERA_VERSION)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_GNU_SOURCE
AC_LANG(C++)
AC_PROG_INSTALL
AC_PROG_MAKE_SET

# Init automake stuff
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER([config.h])
AM_GNU_GETTEXT

# Init gettext
ALL_LINGUAS="si"
AM_GNU_GETTEXT

GETTEXT_PACKAGE=scim-wijesekera
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [The gettext domain])

# Init libtool
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
AC_LIB_LTDL
AC_SUBST(LIBTOOL_DEPS)

# Checks for libraries.
SCIM_VERSION=0.99.8

PKG_CHECK_MODULES(SCIM,[scim >= $SCIM_VERSION])

# Check if we should build setup module
PKG_CHECK_MODULES(SCIM_GTKUTILS,[scim-gtkutils >= $SCIM_VERSION],
		  		[SCIM_HAS_GTKUTILS=yes],
				[SCIM_HAS_GTKUTILS=no])


AC_SUBST(SCIM_VERSION)

AM_CONDITIONAL(SCIM_BUILD_SETUP, [test "$SCIM_HAS_GTKUTILS" = "yes"])

if test "$SCIM_HAS_GTKUTILS" = "yes"; then
  SCIM_BUILD_SETUP=1
else
  SCIM_BUILD_SETUP=0
fi

AC_SUBST(SCIM_BUILD_SETUP)

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([libintl.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([memset])
AC_SUBST(ac_aux_dir)

# libtool option to control which symbols are exported
# right now, symbols starting with _ are not exported
LIBTOOL_EXPORT_OPTIONS='-export-symbols-regex "^[[^_]].*"'
AC_SUBST(LIBTOOL_EXPORT_OPTIONS)

# Extra args.
AC_ARG_ENABLE(debug,
	      [  --enable-debug     Turn on debugging],
	      [case "${enableval}" in
	       yes) debug=yes ;;
	       no)  debug=no ;;
	       *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
       	      esac],[debug=no])

if test "x$debug" = "xyes"; then
  test "$cflags_set" = set || CFLAGS="$CFLAGS -g"
  test "$cppflags_set" = set || CPPFLAGS="$CXXFLAGS -g"
  SCIM_DEBUG_FLAGS="-DENABLE_DEBUG=1"
else
  SCIM_DEBUG_FLAGS=""
fi
AC_SUBST(SCIM_DEBUG_FLAGS)

SCIM_ICONDIR=`$PKG_CONFIG --variable=icondir scim`
SCIM_MODULEDIR=`$PKG_CONFIG --variable=moduledir scim`

if test "x$SCIM_ICONDIR" = "x"; then
  SCIM_ICONDIR=${datadir}/scim/icons
fi

if test "x$SCIM_MODULEDIR" = "x"; then
  SCIM_MODULEDIR=${libdir}/scim-1.0
fi

AC_SUBST(SCIM_ICONDIR)
AC_SUBST(SCIM_MODULEDIR)

AC_CONFIG_FILES([Makefile 
	intl/Makefile 
	po/Makefile.in
	data/Makefile
	src/Makefile
])
AC_OUTPUT
