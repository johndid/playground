#!/bin/sh

all_ids=$(find $1 -type f -name '*.cpp' -print0 -or -name '*.dfm' -print0 -or -name '*.h' -print0 -or -name '*.CPP' -print0 -or -name '*.DFM' -print0 -or -name '*.H' -print0| xargs -0 egrep -won "(\"|')\*[^.]*(\"|')");

for id in $all_ids
do
     # fetch filename line number and the actual ID from the code base
    file=$(echo $id | awk 'match($0,/^.+:[0-9]/) { print substr($0,RSTART,RLENGTH -2) }');
    line_num=$(echo $id | awk 'match($0,/:[0-9]+:/) { print substr($0,RSTART,RLENGTH) }');
    single_id=$(echo $id | awk 'match($0,/\*[^.]+$/) { print substr($0,RSTART,RLENGTH) }');
    out_id=${single_id%%\"};
    out_id=${out_id%%\'};
    ! test -z $file && ! test -z $line_num && ! test -z $single_id && echo "${out_id%%'}\t\t\t$line_num\t$file";
done

