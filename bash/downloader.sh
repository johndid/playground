#!/bin/bash

#html=$(wget "-q -O $1");
#echo $html;
grep $1 | sed 's/^.*<a href="//' | sed 's/".*$//'
