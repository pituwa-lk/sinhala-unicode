#!/bin/bash
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

TRANSLATION_FILE=si.po
TMPDIR=/tmp
BASE_LC=de
OUR_LC=si
FILELIST=filelist

for PREFIX in /usr /usr/kde/[34]*
do

LOCALE_DIR=$PREFIX/share/locale
WORKING_DIR=$TMPDIR/si.tmp

if [ ! -f $TRANSLATION_FILE ]
then
	echo "Can't open translation file $TRANSLATION_FILE"
	continue 1
fi
echo "Using translation file $TRANSLATION_FILE"


if [ ! -d $LOCALE_DIR ]
then
	echo "Locale directory not found"
	continue 2
fi
echo "Locales found in $LOCALE_DIR"


if [ ! -d $LOCALE_DIR/$BASE_LC ]
then
	echo "Base locale not found"
	continue 3
fi
echo "Using $BASE_LC in $LOCALE_DIR/$BASE_LC as base locale"


rm -rf $WORKING_DIR
if ! mkdir -p $WORKING_DIR
then
	echo "Can't create tempory directory $WORKING_DIR"
	continue 4
fi
echo "Created $WORKING_DIR"
cp $TRANSLATION_FILE $WORKING_DIR
cp si.pl $WORKING_DIR
cd $WORKING_DIR


cp -R $LOCALE_DIR/$BASE_LC/* .
echo "Working on a copy of $BASE_LC"


rm -rf $FILELIST
for i in `find -name '*.mo'`
do
	echo -n "    Converting $i..."
	j=`echo $i | sed 's/\.mo$//'`
	msgunfmt -o $j.po $i 2> /dev/null
	echo $j.po >> $FILELIST
	rm -f $i
	echo "done"
done

./si.pl < $TRANSLATION_FILE

find -name '*.po' -exec mv -f {}.new {} \;

for i in `find -name '*.po'`
do
	echo -n "Converting $j ..."
	j=`echo $i | sed 's/\.po$//'`
	msgfmt -o $j.mo $i 2> /dev/null
	rm -f $i
	echo "done"
done

find -name '*.mo' | cpio -pm $LOCALE_DIR/$OUR_LC

cd -
rm -rf $WORKING_DIR

done

