#!/bin/bash
#
# Copyright (C) 2004 by Anuradha Ratnaweera
#
# This is a general purpose script to clean up an autoconf,
# automake, autoheader based package.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

echo -n Cleaning the source tree...
make distclean > /dev/null 2>&1
echo done.

echo -n Removing unnecessary files...
rm -rf aclocal.m4 autom*.cache config.h config.h.in config.log \
	config.status configure depcomp install-sh missing \
	config.guess config.sub ltmain.sh \
	mkinstalldirs stamp-h* gtk-im-sinhala*.tar.gz *~
rm -f `find -name 'Makefile'`
rm -f `find -name 'Makefile.in'`
rm -rf `find -name '.deps'`
echo done.

