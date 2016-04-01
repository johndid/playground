#!/bin/bash

i=1
for f in *.$1; do 
#   echo Renaming file \"$f\" to \"image_${i}.$1\"
#   echo Renaming file \"$f\" to \"image_${i}.$1\"
#   mv "$f" "${i}_${n}"
   mv -v "$f" "install_${i}.$1"
   i=$((i+1))
done

