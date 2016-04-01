#!/bin/bash

files=$(ls $1*.txt);
src_file=$2
out_file=tmp.txt

for file in $files;
do
    echo $file;
    
    struct=$(cat $file | grep '(static' | perl -p -e "s/\(static (.*)\) .*$/\$1/g");
    members=$(cat $file | perl -p -e 's/bytes, /\n/g' | perl -p -e 's/public:|private://g'  | perl -p -e 's/\[([0-9]+)\] (.+) (.+)(,|\))/~$3,$1/g' | grep '~' | perl -p -e 's/~| +//g');

    for member in $members; 
    do
	cat $src_file | sed "/TEST_SIZE(\"$struct/ a\ TEST_INDEX($struct,$member);" > $out_file
	cp $out_file $src_file;
    done
done

#perl -p -e 's/; T/;\nT/g' $out_file;