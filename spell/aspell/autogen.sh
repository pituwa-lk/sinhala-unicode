#!/bin/bash

echo -n 'Cleaning the tree...'
if [ -f Makefile ] ; then
    make clean > /dev/null 2>&1
fi
./clean.sh
echo 'done.'

echo -n 'Creating character data...'
./mkchardata u-sinh.txt
echo 'done.'

echo -n 'Autogenerating files...'
./proc create
echo 'done.'

echo -n 'Creating package...'
PACKAGE=aspell-si-0.60-0
mkdir $PACKAGE
cp * $PACKAGE/ 2> /dev/null
tar -czf $PACKAGE.tar.gz $PACKAGE/
rm -rf $PACKAGE/
echo 'done.'

echo
echo "Package $PACKAGE.tar.gz successfully created. :-)"
echo

