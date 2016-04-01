#!/bin/bash

# This script sets the proxy settings for firefox based on the gnome $all_proxy variable!
prefs=$(find .mozilla/firefox/*.default/ -maxdepth 1 -type f -name  'prefs.js')

test -z $prefs && echo "Can't find mozilla prefs.js!" && exit 1
test -z $all_proxy && echo "You'll have to run: mate-network-properties to set the system wide proxy first" && exit 2

proxy=$(echo $all_proxy | perl -p -e "s|socks://(.+):(.+)/|\1|g")
port=$(echo $all_proxy | perl -p -e "s|socks://(.+):(.+)/|\2|g")

perl -p -i -e "s|(network[.]proxy[.].+\",\s+\").+(\")|\1$proxy\2|g" $prefs
perl -p -i -e "s|(network[.]proxy[.].+\",\s+)[0-9][0-9][0-9][0-9][0-9]?(\))|\1 $port\2|g" $prefs