#!/bin/bash

DIR=$1
FILE_EXT=$2

files=$(find $DIR -name $FILE_EXT -type f)

echo"These files are up for spell checking: $files"

for file in $files; do
    echo "aspell check $file"
    aspell check $file
done