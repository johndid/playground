#!/bin/bash

dir=$1
cropfiles=$(find $1 -name '*.png')

for file in $cropfiles;do
#    echo "convert $file -crop 800x650+160+80 $dirwd_$(basename $file)"
    convert $file -crop 850x700+160+80 $dirwd_$(basename $file)
done