#!/bin/bash

ARRAY=(foo bar baz)

for element in ${ARRAY[*]}; do
    echo $element
done