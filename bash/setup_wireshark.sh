#!/bin/bash

user=$USER
sudo dpkg-reconfigure wireshark-common 
sudo usermod -a -G wireshark $user
echo "Close the terminal esse, or log in and outta gnome! Unless you don't wan't the setup to work."