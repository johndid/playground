#!/bin/sh
# example program graps the command line arguments and plugs them in a file

echo $PWD:gcc:"$@" >> /tmp/buildlog
args=$(echo "$@" | perl -p -e "s/-g|-O2|-MT .+[.]o|-MD|-MF|-MP|-MR//g")
args=$(echo "$args" | perl -p -e "s/[.]deps/-I .deps/g")
args=$(echo "$args" | perl -p -e "s/-o .+[.]o//g")
args=$(echo "$args" | perl -p -e "s/-lfl//g")
args=$(echo "$args" | perl -p -e "s/ +//g")

gcc "$@"

echo "$args" >> /tmp/buildlog
flexilint +v "$args" >> /tmp/lint.txt
