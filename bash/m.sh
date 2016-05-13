#!/bin/bash
## usage: ./magnet.sh "magnet_uri" or ./magnet.sh "file containing magnet uri's"

function torrent()
{
    # The trick to non greedy perl reges is the (.*?) part. Which says group () the match .* but only zero or 1 ? time
    # the rest &dn= is the magnet denotation, and & is the first denotator after the magnet name (typically &tr= for the tracker)
    # the reason for the perl reges is that there can be multiple trackers in the magnet uri. Using greedy regex will match all of
    # these
    arr=$(echo "$item" | perl -pe 's|.*[&]dn[=](.*?)[&].*|\1|');
    decoded=$(echo -e `echo $arr | sed 's/+/./g;s/%/\\\\x/g;'`)
    [[ "$1" =~ xt=urn:btih:([^&/]+) ]] || exit;
    echo "d10:magnet-uri${#1}:${1}e" > "$decoded.torrent"
    echo "wrote: $decoded.torrent"
}

if [ -f "$1" ];then 
    for item in $(cat $1 | grep 'urn'); do
	torrent "$item"
    done
else
    torrent "$1" 
fi
