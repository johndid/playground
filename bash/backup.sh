#!/bin/sh

usage_txt="Usage: $0 [backup destination dir] (I'm reading your home dir!)"

test ! -d "$1" && echo $usage_txt

backup_path=$1
version=$(date --rfc-3339 seconds | perl -p -e "s/ /-/g" | perl -p -e "s/:/./g" | perl -p -e "s/[+].*$//g")
filename=~/john-$version.tar.gz

tar -czvf $filename $backup_path
exit 0;
