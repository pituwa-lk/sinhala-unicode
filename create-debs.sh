#!/bin/bash

topdir=$(pwd)
tmpdir=/tmp/sinhala-gnu-linux-deb

rm -rf $tmpdir || exit 1
mkdir -p $tmpdir/deb || exit 1

get_version () {
	version=$(dpkg-parsechangelog | grep '^Version: ' | sed 's/^Version:[[:space:]]*\([^-]*\).*/\1/')
}

make_package () {

	cd $pkgdir0 || exit 1
	version=''
	get_version
	[ "$version" ] || exit 1
	cd - > /dev/null

	pkgdir=$pkgname-$version
	[ "$pkgdir" ] || exit 1

	cp -R $pkgdir0 $tmpdir/$pkgdir || exit 1

	cd $tmpdir || exit 1

	$pkgdir/cleanup.sh || exit 1
	rm -f $pkgdir/cleanup.sh
	find $pkgdir -name CVS -prune -exec rm -rf {} \;

	if [ -x "$pkgdir/autogen.sh" ]
	then
		cd "$pkgdir"
		sh autogen.sh || exit 1
		./configure || exit 1
		make dist || exit 1
		mv $pkgname*.tar.gz .. || exit 1
		cd ..
		rm -rf $pkgdir || exit 1
		tar -xzvf $pkgname*.tar.gz || exit 1
		rm -f $pkgname*.tar.gz
	fi

	chmod +x $pkgdir/debian/rules

	dpkg-source -b $pkgdir || exit 1

	rm -rf $pkgdir
	mv $pkgname* deb || exit 1
	cd $topdir
}

#
# sinhala-gnu-linux
#

pkgdir0=debian
pkgname=sinhala-gnu-linux
make_package

#
# sinhala-font-lklug
#

pkgdir0=fonts
pkgname=sinhala-font-lklug
make_package

#
# sinhala-locale-glibc
#

pkgdir0=locale/glibc
pkgname=sinhala-locale-glibc
make_package

#
# scim-sinhala-trans
#

pkgdir0=scim/trans
pkgname=scim-sinhala-trans
make_package

