#!/bin/sh
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
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
#

#
# glibc locales
#

echo
echo 'Adding si_LK.UTF-8 to glibc...'
echo

echo -n 'Copying si_LK locale...'
cp si_LK /usr/share/i18n/locales/
echo 'done.'

echo -n 'Creating directories for PO files...'
mkdir -p /usr/share/locale/si/LC_MESSAGES
mkdir -p /usr/share/locale/si/LC_TIME
echo 'done.'

echo -n 'Looking for alias si...'
if grep '^[ 	]*si[ 	][ 	]*si_LK\.UTF-8[ 	]*$' /etc/locale.alias > /dev/null 2>&1 ; then
	echo 'found.'
else
	echo -n 'not found; adding...'
	echo 'si	si_LK.UTF-8' >> /etc/locale.alias
	echo 'done.'
fi

echo -n 'Looking for alias si_LK...'
if grep '^[ 	]*si_LK[ 	][ 	]*si_LK\.UTF-8[ 	]*$' /etc/locale.alias > /dev/null 2>&1 ; then
	echo 'found.'
else
	echo -n 'not found; adding...'
	echo 'si_LK	si_LK.UTF-8' >> /etc/locale.alias
	echo 'done.'
fi

if [ -f /etc/debian_version ] ; then
	echo 'This seems to be a Debian GNU/Linux system.'
	echo -n 'Looking for "si_LK UTF-8" in /etc/locale.gen.'
	if grep '^[ 	]*si_LK[ 	][ 	]*UTF-8[ 	]*$' /etc/locale.gen > /dev/null 2>&1; then
		echo 'found.'
	else
		echo -n 'not found; adding...'
		echo 'si_LK	UTF-8' >> /etc/locale.gen
		echo 'done.'
		echo -n 'Running locale-gen (may take some time)...'
		locale-gen > /dev/null 2>&1
		echo 'done.'
	fi
else
	echo -n 'Running localedef...'
    localedef -i si_LK -f UTF-8 -A /etc/locale.alias si_LK
	echo 'done.'
fi

echo
echo 'si_LK.UTF-8 added to glibc.'

#
# X locales
#

echo
echo 'Adding si_LK.UTF-8 to X...'
echo

echo -n 'Looking for si in compose.dir...'
if grep '^[ 	]*en_US.UTF-8\/Compose[ 	][ 	]*si_LK\.UTF-8[ 	]*$' /usr/X11R6/lib/X11/locale/compose.dir > /dev/null 2>&1 ; then
	echo 'found.'
else
	echo -n 'not found; adding...'
	echo '/^[ 	]*en_US.UTF-8\/Compose[ 	][ 	]*sk_SK.UTF-8[ 	]*$
i
en_US.UTF-8/Compose	si_LK.UTF-8
.
w' | ed /usr/X11R6/lib/X11/locale/compose.dir > /dev/null 2>&1
	echo 'done.'
fi

echo -n 'Looking for si: in compose.dir...'
if grep '^[ 	]*en_US.UTF-8\/Compose:[ 	][ 	]*si_LK\.UTF-8[ 	]*$' /usr/X11R6/lib/X11/locale/compose.dir > /dev/null 2>&1 ; then
	echo 'found.'
else
	echo -n 'not found; adding...'
	echo '/^[ 	]*en_US.UTF-8\/Compose:[ 	][ 	]*sk_SK.UTF-8[ 	]*$
i
en_US.UTF-8/Compose:	si_LK.UTF-8
.
w' | ed /usr/X11R6/lib/X11/locale/compose.dir > /dev/null 2>&1
	echo 'done.'
fi

echo -n 'Looking for si in locale.dir...'
if grep '^[ 	]*en_US.UTF-8\/XLC_LOCALE[ 	][ 	]*si_LK\.UTF-8[ 	]*$' /usr/X11R6/lib/X11/locale/locale.dir > /dev/null 2>&1 ; then
	echo 'found.'
else
	echo -n 'not found; adding...'
	echo '/^[ 	]*en_US.UTF-8\/XLC_LOCALE[ 	][ 	]*sk_SK.UTF-8[ 	]*$
i
en_US.UTF-8/XLC_LOCALE	si_LK.UTF-8
.
w' | ed /usr/X11R6/lib/X11/locale/locale.dir > /dev/null 2>&1
	echo 'done.'
fi

echo -n 'Looking for si: in locale.dir...'
if grep '^[ 	]*en_US.UTF-8\/XLC_LOCALE:[ 	][ 	]*si_LK\.UTF-8[ 	]*$' /usr/X11R6/lib/X11/locale/locale.dir > /dev/null 2>&1 ; then
	echo 'found.'
else
	echo -n 'not found; adding...'
	echo '/^[ 	]*en_US.UTF-8\/XLC_LOCALE:[ 	][ 	]*sk_SK.UTF-8[ 	]*$
i
en_US.UTF-8/XLC_LOCALE:	si_LK.UTF-8
.
w' | ed /usr/X11R6/lib/X11/locale/locale.dir > /dev/null 2>&1
	echo 'done.'
fi

echo -n 'Looking for si in locale.alias...'
if grep '^[ 	]*si[ 	][ 	]*si_LK\.UTF-8[ 	]*$' /usr/X11R6/lib/X11/locale/locale.alias > /dev/null 2>&1 ; then
	echo 'found.'
else
	echo -n 'not found; adding...'
	echo '/^[ 	]*sk[ 	][ 	]*
i
si						si_LK.UTF-8
.
w' | ed /usr/X11R6/lib/X11/locale/locale.alias > /dev/null 2>&1
	echo 'done.'
fi

echo -n 'Looking for si_LK in locale.alias...'
if grep '^[ 	]*si_LK[ 	][ 	]*si_LK\.UTF-8[ 	]*$' /usr/X11R6/lib/X11/locale/locale.alias > /dev/null 2>&1 ; then
	echo 'found.'
else
	echo -n 'not found; adding...'
	echo '/^[ 	]*si[ 	][ 	]*
a
si_LK					si_LK.UTF-8
.
w' | ed /usr/X11R6/lib/X11/locale/locale.alias > /dev/null 2>&1
	echo 'done.'
fi

echo -n 'Looking for si: in locale.alias...'
if grep '^[ 	]*si:[ 	][ 	]*si_LK\.UTF-8[ 	]*$' /usr/X11R6/lib/X11/locale/locale.alias > /dev/null 2>&1 ; then
	echo 'found.'
else
	echo -n 'not found; adding...'
	echo '/^[ 	]*sk:[ 	][ 	]*
i
si:						si_LK.UTF-8
.
w' | ed /usr/X11R6/lib/X11/locale/locale.alias > /dev/null 2>&1
	echo 'done.'
fi

echo -n 'Looking for si_LK: in locale.alias...'
if grep '^[ 	]*si_LK:[ 	][ 	]*si_LK\.UTF-8[ 	]*$' /usr/X11R6/lib/X11/locale/locale.alias > /dev/null 2>&1 ; then
	echo 'found.'
else
	echo -n 'not found; adding...'
	echo '/^[ 	]*si:[ 	][ 	]*
a
si_LK:					si_LK.UTF-8
.
w' | ed /usr/X11R6/lib/X11/locale/locale.alias > /dev/null 2>&1
	echo 'done.'
fi

echo
echo 'si_LK.UTF-8 added to X'

echo
echo 'Check /etc/locale.alias and make sure that si and si_LK alias'
echo 'are in the alphabetically correct place.'
echo

