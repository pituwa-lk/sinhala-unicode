AC_INIT(scim-sayura, 0.3.1, anuradha@taprobane.org)
AC_CONFIG_SRCDIR([configure.ac])

AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(config.h)

AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL
dnl AC_LIB_LTDL
AC_SUBST(LIBTOOL_DEPS)

AC_PROG_CXX
AC_PROG_CC
AC_LANG(C++)

AC_C_CONST
AC_TYPE_SIZE_T

SCIM_VERSION=0.99.8

PKG_CHECK_MODULES(SCIM,[scim >= $SCIM_VERSION])
AC_SUBST(SCIM_VERSION)

# Checks for header files.
AC_HEADER_STDC
AC_FUNC_ALLOCA
dnl AC_CHECK_HEADERS([argz.h fcntl.h langinfo.h libintl.h limits.h locale.h malloc.h stddef.h stdio_ext.h sys/param.h wchar.h])

# libtool option to control which symbols are exported
# right now, symbols starting with _ are not exported
LIBTOOL_EXPORT_OPTIONS='-export-symbols-regex "^[[^_]].*"'

# Extra args.
AC_ARG_ENABLE(debug, [  --enable-debug     Turn on debugging],
	[case "${enableval}" in
		yes) debug=yes ;;
		 no) debug=no ;;
		  *) AC_MSG_ERROR(bad value ${enableval} for --enable-debug) ;;
	esac], [debug=no])

SCIM_ICONDIR=`$PKG_CONFIG --variable=icondir scim`
SCIM_MODULEDIR=`$PKG_CONFIG --variable=moduledir scim`

if test "x$SCIM_ICONDIR" = "x"
then
	SCIM_ICONDIR=${datadir}/scim/icons
fi

if test "x$SCIM_MODULEDIR" = "x"
then
	SCIM_MODULEDIR=${libdir}/scim-1.0
fi

AC_SUBST(SCIM_ICONDIR)
AC_SUBST(SCIM_MODULEDIR)
        
AC_CONFIG_FILES([
	Makefile
	src/Makefile
	data/Makefile
	debian/Makefile
])

AC_OUTPUT

