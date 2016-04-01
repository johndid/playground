#!/bin/bash

    # result=$( cat $1 );
    # for line in ${result[@]};do
    # 	panel=$(grep "/$line<" $2);
    # 	if [ -z $panel ];then
    # 	    echo $line;
    # 	else
    # 	    echo $panel;
    # 	fi
    # done

navigation_order="$1";
search_path="$2";
file_type="$3";
temp_list="temp";

rm $temp_list;

# create a file with the list of all found panels
files=$( find $search_path -name "*$file_type" -type f );
for file in ${files[@]};do
    name=$(basename $file $file_type);
    path=$(dirname $file|cut -d"/" -f5-);
    txt="$path/$name";
    echo "$txt" >> $temp_list
done

#echo ${files_xml} > $temp_list 

# sort the list according to navigation order
result=$( cat $navigation_order );
for line in ${result[@]};do
    panel=$(grep "/$line<" $temp_list);
    if [ -z $panel ];then
	files_xml+=("\t<path>$line</path>\n");
    else
	files_xml+=($panel)
    fi
done

echo ${files_xml[@]}



