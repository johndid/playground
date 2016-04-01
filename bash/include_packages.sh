#!/bin/sh

packages=$(find $1 -name '*.deb' -type f -not -name '*linux-iso*')
#repository=$(find $2 -name '*.deb' -type f)

cd $2

for package in $packages; do
    version=$(dpkg --info $package|grep Version | cut -c 11-);
    echo $package "->" $version;

    reprepro includedeb mk3 $package

done

cd -



