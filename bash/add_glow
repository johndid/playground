#!/bin/sh

USAGE="$0 [source_dir] [dest_dir] all images from source will be substituded to <imagename>.glow.<imageextention>"
IMG_SRC_DIR=$1
IMG_DEST_DIR=$2

if [ -n "$IMG_SRC_DIR" -a -d "$IMG_SRC_DIR" ]; then
    if [ -n "$IMG_SRC_DIR" -a -d "$IMG_DEST_DIR" ]; then
	for IMG in $(ls $IMG_SRC_DIR); do
	    DEST_IMG=$(basename $IMG)
	    echo "prosessing $IMG"
	    glow -a 1.7 -s 16 $IMG $IMG_DEST_DIR/${DEST_IMG%%.png}.glow.png
	done
	exit 0

    else
	echo "No dest directory"
    fi
else
    echo "No source directory"
fi
echo "$USAGE"
exit 1