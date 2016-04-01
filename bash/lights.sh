#!/bin/bash	

ROOT_UID="0"
if [ "$UID" -eq "$ROOT_UID" ] ; then
    status=$(grep status /proc/acpi/ibm/light | cut -c 10-);
    if [ "$status" = "on" ]; then
	echo "off" > /proc/acpi/ibm/light;
    else
	echo "on" > /proc/acpi/ibm/light;
    fi 
else
    echo "Only the mighty root may say: 'let there be light'";
    exit 1
fi

