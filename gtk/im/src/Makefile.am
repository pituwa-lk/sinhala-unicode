#
# Copyright (C) 2004 by Anuradha Ratnaweera
#
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; either version 2.1 of the
# License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
# USA
#

AM_CFLAGS = $(GTK_CFLAGS)

localedir = $(datadir)/locale
AM_CPPFLAGS = -DLOCALEDIR=\"$(localedir)\" -DGTK_DISABLE_DEPRECATED=1

moduledir = $(libdir)/gtk-2.0/$(GTK_BINARY_VERSION)/immodules
module_LTLIBRARIES = im-sinhala-p.la

im_sinhala_p_la_LDFLAGS = -rpath $(moduledir) -avoid-version -module
im_sinhala_p_la_SOURCES = imsinhala-p.c
im_sinhala_p_la_LIBADD = @GTK_LIBS@

noinst_PROGRAMS = im-module-file
im_module_file_SOURCES = im-module-file.c
im_module_file_LDADD = @GTK_LIBS@

all-local: gtk.immodules

gtk.immodules: $(module_LTLIBRARIES)
	$(GTK_QUERY_IMMODULES) $(module_LTLIBRARIES) > gtk.immodules ;

install-data-hook: im-module-file
	GTK_PATH=$$GTK_PATH:$(DESTDIR)$(libdir)/gtk-2.0 $(GTK_QUERY_IMMODULES) > `./im-module-file` ;

MOSTLYCLEANFILES = gtk.immodules

