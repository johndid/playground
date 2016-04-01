#query for needed packages!!! Not enough with just uck as the version is sucky

dependencies="gfxboot-dev, squashfs-tools, squashfs-tools-dbg, mktemp"

for each $dependency in $dependencies;
do
    echo $dependency;
    dpgk-query -W $dependency | test -z && sudo aptitude install $dependency;
done

sudo dpkg -i tools/uck_2.4.6-0ubuntu1_all.deb 
