#!/usr/bin/env bash


if [ -f "$1" ]; then
    FILE="$1";
    
    # save and change IFS 
    OLDIFS=$IFS
    IFS=$'<hr>'
    
    # read all file name into an array
    fortuneArray=($())
    
    # restore it 
    IFS=$OLDIFS
    
    # get length of an array
    tLen=${#fortuneArray[@]}
    
    # use for loop read all filenames
    for (( i=0; i<${tLen}; i++ ));
    do
	echo "Do stuff with each item here: ${fileArray[$i]} ${fileArray[$i]:0:-3}ps"
    done

else
    echo "usage [directory]"
fi


# sed -e ‘s/<[^>]*>//g’

sed 's|<h[2-3][^>]*>|%|g' Documents/The\ Tao\ Of\ Programming_formatted.html | sed 's|<[^>]*>||g' | sed 's|^ ||g' | tr -s " " | sed 's|^[%] .*$|%|g' | sed '|$^|d'
