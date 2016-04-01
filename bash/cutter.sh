#/bin/bash

file=$1;
sed_file=$2 
output=$3 

struct=$(cat $file | grep '(static' | perl -p -e "s/\(static (.*)\) .*$/\$1/g");
members=$(cat $file | perl -p -e 's/bytes, /\n/g' | perl -p -e 's/public:|private://g'  | perl -p -e 's/\[([0-9]+)\] (.+) (.+)(,|\))/~$3,$1/g' | grep '~' | perl -p -e 's/~| +//g');

for member in $members; 
do
    ARRAY+=("TEST_INDEX($struct,$member);");
done

sed "/TEST_SIZE(\"$struct/ a\ ${ARRAY[*]}" $sed_file > $output

