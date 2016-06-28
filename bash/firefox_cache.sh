#!/usr/bin/env bash
#script to create an ramdisk for firefox
[ ! -d /Volumes/firefox_cache ] && diskutil erasevolume HFS+ "firefox_cache" `hdiutil attach -nomount ram://1048576`
