#!/usr/bin/env bash

# TODO: add options to manipulate the warious url schemes
# like -m for getting only mail. And -h for only http
# plus -m and -p in combination
# The script shoudl not care for anything else. Checking
# the actual urls should go some where else.
# Could this be done easier in node.js ??

if [ -n "$1" ];then
    if [ -n "$2" ];then
	site=$1
	file=$2
	urls=$(grep -oE 'href="([^"#]+)"' $2 | grep -v "css" | cut -d '=' -f2 | tr -d '"')	

	for url in ${urls[@]}; do

	    case "${url}" in
		# could this be used instead of the other entry??? -> https?://*)
		http://*)		
		    echo $url
		    ;;
		https://*)
		    echo $url
		    ;;
		mailto:*)
		    echo $url
		    ;;
		*)
		    echo $1${url: +1};
		    ;;
	    esac
	done
	exit 0;
    fi
fi

cat << USAGE
broken url test script v0.1

Usage:

  $(basename $0) [site] [file]

  Where:
  site is an http(s) address of the site to verify the urls
  file is a file containing the urls


USAGE
exit 1;

#
# Using: something like: list = $(document).a ???
# And how do you setup the URLS so the headers is the only thing to check???
#
#command to test using curl on files
#CURL="curl -s -D - URI -o /dev/null"
# use with the curl statement above:  echo $(echo "$CURL" | sed "s|URI|$url|");
#command to send a command line test mail
# echo "mail -s 'Test' -a"."$(echo $url | cut -d':' -f2) <<< 'This is a mail from the broken.url.sh testing tool'";
#
#		    echo "lynx -source $1${url: +1} > ${url##/*/}.html"
#		    echo "lynx -source $1${url: +1} > ${url##/*/}"
#		    lynx -source $1${url: +1} > ${url##/*/}
