#!/bin/sh

program=macro_dumper

gcc $program.c -o $program

./macro_dumper
if [ "$?" -eq "0" ]; then
    echo "non override mode - ok"
else
    echo "non override mode - fail"
fi


./macro_dumper 3
if [ "$?" -gt "0" ]; then
    echo "override mode - ok"
else
    echo "override mode - fail"
fi

