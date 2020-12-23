#!/bin/sh

PHP_CONFIG=`which php-config$1`
if [ -z "$1" ]
then
	echo "Argument 1 must be the php version"
	exit
fi
if [ ! -x "$PHP_CONFIG" ]
then
	echo "Invalid version $1";
	exit
fi
PHP_VERSION=$1
PKG_WORK=pkgwork
EXTENSION_DIR=`$PHP_CONFIG --extension-dir`
INI_DIR=`$PHP_CONFIG --ini-dir`
RINDOW_OPENBLAS_VERSION=`fgrep "# define PHP_RINDOW_OPENBLAS_VERSION" php_rindow_openblas.h | cut -d " " -f 4 | cut -d "\"" -f 2`
. /etc/os-release
OS_VERSION=$ID$VERSION_ID
echo $ID
rm -rf $PKG_WORK
mkdir -p $PKG_WORK$EXTENSION_DIR
mkdir -p $PKG_WORK$INI_DIR
mkdir -p $PKG_WORK/DEBIAN
cp modules/rindow_openblas.so $PKG_WORK$EXTENSION_DIR/.
chmod 744 $PKG_WORK$EXTENSION_DIR/rindow_openblas.so
cp conf/20-rindow_openblas.ini $PKG_WORK$INI_DIR/.
chmod 744 $PKG_WORK$INI_DIR/20-rindow_openblas.ini 
sed -e s/%PHP_RINDOW_OPENBLAS_VERSION%/$RINDOW_OPENBLAS_VERSION/ debian/control | \
sed -e s/%OS_VERSION%/$OS_VERSION/ | \
sed -e s/%PHP_VERSION%/$PHP_VERSION/ > $PKG_WORK/DEBIAN/control
#sed -e s@%EXTENSION_DIR%@$EXTENSION_DIR@ debian/rules | \
#sed -e s@%INI_DIR%@$INI_DIR@ debian/rules | \
#	> $PKG_WORK/DEBIAN/rules
#cp debian/changelog $PKG_WORK/DEBIAN/.
#cp debian/copyright $PKG_WORK/DEBIAN/.

rm -f rindow-openblas*.deb
fakeroot dpkg-deb --build pkgwork .
