#!/bin/bash
# Script to change the desktop image when switching workspaces.
# Tested on Linux Mint 13 'cinnamon'
desktop_dir="/usr/share/backgrounds/user" # full path to images directory; 
desktop_img[0]="img1.jpg"
desktop_img[1]="img2.jpg"
desktop_img[2]="img3.jpg"
desktop_img[3]="img4.jpg"
# add more images if using more workspaces

setdesktop() {
    mateconftool-2 -t str --set /desktop/mate/background/picture_filename $desktop_dir/$1
   }

xprop -root -spy _NET_CURRENT_DESKTOP | (
   while read -r; do
      desk=${REPLY:${#REPLY}-1:1}
      setdesktop ${desktop_img[$desk]}
   done
   )
