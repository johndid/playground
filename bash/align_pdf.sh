#!/usr/bin/env bash


if [ -d "$1" ]; then
    DIR="$1";
    
    # save and change IFS 
    OLDIFS=$IFS
    IFS=$'\n'
    
    # read all file name into an array
    fileArray=($(find $DIR -type f -name '*.pdf'))
    
    # restore it 
    IFS=$OLDIFS
    
    # get length of an array
    tLen=${#fileArray[@]}
    
    # use for loop read all filenames
    for (( i=0; i<${tLen}; i++ ));
    do
	pdf2ps ${fileArray[$i]} ${fileArray[$i]:0:-3}ps
    done

else
    echo "usage [directory]"
fi
