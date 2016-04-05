#!/bin/bash

function usage ()
{
echo "Usage:"
echo "  map_network_drives.sh windows_share (src) local_directory (dest) windows_domain (DOMAIN)"
echo "  you'll be queried for your windows password during mount"
}

# This function checks the destination directory for existance, mountage etc. and creates everything
# if the required destination directories are not available.
# Once everything is setup the function mounts the samba network drive
#
# $1 must contain the password for the drive
# $2 must contain the destination drive
# $3 must contain the source samba drive to mount
function fix_drive()
{
    passwd=$1;
    drive=$2;
    samba_drive=$3;
    DOMAIN=$4
    echo "Mapping network drive $3 as $2"
    ! test -d $drive && mkdir -p $drive;
    test -n "$(grep "$drive" /etc/mtab)" && sudo umount $drive
    sudo mount -t cifs $samba_drive $drive -o username=$USER,passwd=$passwd,domain=$DOMAIN,iocharset=utf8,file_mode=0777,dir_mode=0777,noserverino,rw,uid=1000
    sudo chown $USER $drive
}

# test ! $1 && usage;
# test ! $2 && usage;
# test ! $3 && usage;

# Check to see if you got a password
# and if not ask for one!
#pass=$1
if [ -z $pass ]; then
    echo -n "Windows password:"
    read -es pass
    echo "\n";
fi


# Paths for the destination directories
WINDOWS_SHARE=$1
USER_SHARE=$2
WINDOWS_DOMAIN=$3
# mount the fuckers!
#fix_drive $pass $USER_SHARE "//<windows_path_for_user_share/" "<DOMAIN>"
fix_drive $pass $USER_SHARE $WINDOWS_SHARE $WINDOWS_DOMAIN

exit 0
