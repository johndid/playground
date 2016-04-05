#!/bin/bash
## usage: ./magnet.sh "magnet_uri"

[[ "$1" =~ xt=urn:btih:([^&/]+) ]] || exit;
echo "d10:magnet-uri${#1}:${1}e" > "magnet-${BASH_REMATCH[1]}.torrent"
