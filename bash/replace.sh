#!/bin/bash

SIZES=$(cat $1)

for size in $SIZES; 
do
    t=$(echo $size | perl -p -e "s/^(.*),(.*)/\$1/g")
    t_size=$(echo $size | perl -p -e "s/^(.*),(.*)/\$2/g")

#    echo "$t -> $t_size"
#    perl -p -e 's/^.*TESTER.*$t.*0x(.*).*;$/john: \$2/g' $2 | grep john
#    echo "s/^((.*TESTER.*$t.*)0x(.*))/\$2 $t_size\);/g"
    perl -p -i -e "s/^((.*TESTER.*$t.*)0x(.*))/\$2 $t_size\);/g" $2

done
