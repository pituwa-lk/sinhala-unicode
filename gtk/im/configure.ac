dnl
dnl Copyright (C) 2004 by Anuradha Ratnaweera
dnl
dnl This library is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Lesser General Public
dnl License as published by the Free Software Foundation; either
dnl version 2.1 of the License, or (at your option) any later version.
dnl 
dnl This library is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl Lesser General Public License for more details.
dnl 
dnl You should have received a copy of the GNU Lesser General Public
dnl License along with this library; if not, write to the Free Software
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
dnl

AC_INIT()
AM_INIT_AUTOMAKE(gtk-im-sinhala, 0.2.0)

AC_PROG_CC
AC_PROG_LIBTOOL
AC_CHECK_PROGS([GTK_QUERY_IMMODULES], [gtk-query-immodules-2.0])

if test "x$GTK_QUERY_IMMODULES" = "x" ;
then
    AC_MSG_ERROR([gtk-query-immodules-2.0 not found.])
fi

PKG_CHECK_MODULES(GTK, gtk+-2.0 >= 2.2.0 pango >= 1.2.3)

GTK_BINARY_VERSION=`pkg-config --variable gtk_binary_version gtk+-2.0`

GETTEXT_PACKAGE=gtk-im-extra
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", 
                   [Define the gettext package to be used])
AM_GLIB_GNU_GETTEXT

AC_SUBST([GETTEXT_PACKAGE])
AC_SUBST([GTK_CFLAGS])
AC_SUBST([GTK_LIBS])
AC_SUBST([GTK_BINARY_VERSION])

AM_CONFIG_HEADER(config.h)
AC_OUTPUT([Makefile src/Makefile po/Makefile])

