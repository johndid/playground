#!/bin/bash

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
    echo "Mapping network drive $3 as $2"
    ! test -d $drive && mkdir -p $drive;
    test -n "$(grep "$drive" /etc/mtab)" && sudo umount $drive
    sudo mount -t cifs $samba_drive $drive -o username=$USER,passwd=$passwd,domain=MD-MAN,iocharset=utf8,file_mode=0777,dir_mode=0777,noserverino,rw,uid=1000
    sudo chown $USER $drive
}

# Check to see if you got a password
# and if not ask for one!
pass=$1
if [ -z $pass ]; then
    echo -n "Windows password:"
    read -es pass
    echo "\n";
fi

# Paths for the destination directories
USER_SHARE=/tmp/user_share

# mount the fuckers!
fix_drive $pass $USER_SHARE "//<windows_path_for_user_share/"

exit 0
