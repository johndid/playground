#!/bin/sh
#
# This is the friendly python3 matplotlib installer script
# it checks for all matplotlib dependencies as pr. Sep 9 2014
# Any additions to the installer must be added by hand!
#
# If none of the dependencies are installed, the script will:
# 1. install prebuild ubuntu packages
# 2. Create a local dir for downloaded files
# 3. install dependencies by downloading these from various sources
# 3.a cython
# 3.b numpy, scipy
# 3.c pyttk
# 3.d matplotlib
# 4. remove the directory after installation
#
# john@dideriksen.org

# 1. 
sudo aptitude install python3 python3-dev python3-setuptools python3-tk python3-cairo python3-cairo-dev libpng-dev
sudo aptitude install gfortran libopenblas-dev liblapack-dev
sudo easy_install3 -U distribute

# 2. 
matlib=/tmp/matlib 
[ -d $matlib ] && sudo rm -rf $matlib
mkdir $matlib && cd $matlib

# 3. Install dependencies, these vary and will change for furure releases!
# As the matplotlib we use in the dse require bleeding edge, we'll grap the latest stuff from the bleeding repositories

# 3.a
cython=$(cython -V)
if [ "$cython" \>  "Cython version 0.20.2" ]; then
    wget http://cython.org/release/Cython-0.20.2.tar.gz && tar -zxvf Cython-0.20.2.tar.gz && cd Cython-0.20.2/ && sudo python3 setup.py install && cd -
fi

# 3.b
#install bleeding edge eggs from git repositories
for package in numpy scipy; do
    version=$(python3 -c "import os,$package;print($package.version.version)")
    if [ -z $version ]; then
	[ -d $package ] && sudo rm -rf $package
	git clone http://github.com/$package/$package.git $package && cd $package && sudo python3 setup.py install && cd -
    else
	echo "$package version $version"
    fi
done

# 3.c
# The pyttk egg is called ttk when using it from inside your python script.
# This forses us to check it seperately as the for loop below will break on
# the ttk vs pyttk naming convension
ttk_version=$(python3 -c "import os,ttk;print(ttk.__version__)")
if [ -z $ttk_version ];then
    sudo easy_install pyttk;
else
    echo "ttk version $ttk_version"
fi

# 3.d
# install bleeding edge eggs using easy_install
# NOTICE: this loop can only be extented if the egg name is the same in both the python code and module name in bash!
for egg in matplotlib; do 
    egg_version=$(python3 -c "import os,$egg;print($egg.__version__)")
    if [ -z "$egg" ]; then
	sudo easy_install3 $egg
    else
	echo "$egg version $egg_version"
    fi
done

cd -

# 4.
sudo rm -rf $matlib
