#!/bin/bash
# Workspace desktop image switcher WDIS 1.0
# Script to change the desktop image when switching workspaces.
# Tested on Linux Mint 13 'cinnamon'
desktop_dir="/home/username/.cinnamon/backgrounds/" # full path to images directory; 
#desktop_img=($(ls -d $desktop_dir/*/))
desktop_img[0]="angry.jpg"
desktop_img[1]="snow-holdup.jpg"
desktop_img[2]="snow.jpg"
desktop_img[3]="xmas-snow.jpg"
# add more images if using more workspaces

setdesktop() {
    gsettings set org.gnome.desktop.background picture-uri "file://$desktop_dir$1"
}

xprop -root -spy _NET_CURRENT_DESKTOP | (
    while read -r; do
	desk=${REPLY:${#REPLY}-1:1}
	setdesktop ${desktop_img[$desk]}
    done
)