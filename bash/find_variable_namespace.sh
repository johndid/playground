#!/bin/sh

include_path=$1
variable_name=$2

#find namespace replacement
namespace_file=$(find $include_path -name '*.h' | xargs egrep "^ *(class|struct|enum) +$variable_name *{?")
if [ -n "$namespace_file" ];then

    filename=$(echo $namespace_file | cut -d ':' -f 1)
    echo "match in: $filename"

    namespace=$(egrep "^ *namespace" $filename)
    new=$(echo $namespace | perl -p -e "s|namespace ||g" | perl -p -e "s| +{ *|::|g")
    echo $new$variable_name

    # Replace old variable with new variable in files except the file containing the definition
    file_list=$(find $include_path -name '*.h' -or -name '*.cpp' | xargs egrep -l " +$variable_name")

    # remove the file containing the variable definition!
    list=$(echo $file_list | perl -p -e "s|$filename||g")

# #remove anyfiles living in the same namespace
# grep -l $new $list

# for file in $list;do
#   echo $file
#   perl -p -e "s|($variable_name)|$new\$1|g" $file | grep -n "$new$variable_name"

# #  perl -p -i -e "s|($variable_name)|$new\$1|g" $file
# #  grep -n "$new$variable_name" $file

# #  perl -p -i -e "s|bes::datatree::||g" $file
# #  grep -n "$variable_name" $file
# done

else
    echo "Variable: $variable_name not found in: $(pwd $include_path)!"
fi