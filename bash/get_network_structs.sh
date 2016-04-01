#!/bin/bash

files=$(find $1 -name '*.h' -type f -or -name '*.cpp' -type f | xargs pcregrep -liM 'PACKED\s?')

# This gives us all files containing the keyword packed for microtec
for file in $files; do
    echo "-------"
    echo "$file:-"
    ~/bin/remove_comments.pl $file | egrep "struct|class"
done

