#!/bin/bash

if [ -f "$1" ]; then

TARGET=/usr/lib/jvm/

#get jvm name, by finding the only file in the kit ending with java, aka the java exefile ;)
JVM=$(tar -tf jre-7u45-linux-i586.tar.gz --wildcards --no-anchored '*java' | cut -d '/' -f 1)
echo "Installing: $JVM to: $TARGET"
sudo tar xzvf $1 --directory $TARGET/
sudo chown -R root:root /usr/lib/jvm/$JVM

# setup the ubuntu update-alternatives to support the new java vesion
PRG=(java javaws)

for executable in ${PRG[*]}; do
    sudo update-alternatives --install "/usr/bin/$executable" "$executable" "/usr/lib/jvm/$JVM/bin/$executable" 1
    sudo chmod a+x /usr/bin/$executable

    echo "NOTICE:"
    echo "You'll need to select the number for: $JVM, from the list below."
    echo "This is the way that you configure java executables for Ubuntu"

    sudo update-alternatives --config $executable
done;

java -version

exit 0;
fi

echo "Usage $0: [Java jre tarball]";
exit 1;