#!/bin/sh

set -e

libtoolize
aclocal
autoheader
automake --add-missing
autoconf

exit 0

