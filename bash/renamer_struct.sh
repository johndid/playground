#!/bin/bash


file=$1
s=$(cat $file | grep '(static ' | perl -p -e "s/\(static (.+)\) +.+$/\$1/g")
mv $file $s.txt

