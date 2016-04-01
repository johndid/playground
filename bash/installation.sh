sudo aptitude update
sudo aptitude upgrade

sudo add-apt-repository ppa:pipelight/stable
sudo aptitude update
sudo aptitude install -r pipelight-multi
sudo pipelight-plugin --update
sudo pipelight-plugin --enable silverlight
sudo pipelight-plugin --enable flash
sudo pipelight-plugin --enable widevine
sudo pipelight-plugin --create-mozilla-plugins

sudo aptitude install -r emacs virtualbox virtualbox-dkms virtualbox-guest-dkms virtualbox-guest-x11 virtualbox-qt virtualbox-guest-additions-iso chromium-browser zenmap at clamav clamav-deamon rdesktop 

sudo -v && wget -nv -O- https://raw.githubusercontent.com/kovidgoyal/calibre/master/setup/linux-installer.py | sudo python -c "import sys; main=lambda:sys.stderr.write('Download failed\n'); exec(sys.stdin.read()); main()"

#clamscan
 # Thunderbird Virus Scan

 #    I have searched a lot and this subject seems ignored. I do not want to get into a discussion about the need for virus scanning in Linux. This is for those who actually want scan for viruses, to ensure they do not forward a virus on to a poor Windows user.

 #    Install Thunderbird, clamassassin, clamav, clam-freshclam.

 #    Set up your accounts in Thunderbird. Then go Tools Add-ons and get more addons. You will need to setup a Mozilla account and get the add on "clamdrib". Download to you home folder, then in Thunderbird Tools Add-ons install clamdrib-0.2-tb.xpi

 #    open a terminal window and sudo dpkg-reconfigure clamav-base

 #    Accept all the defaults except

 #    socket type change to TCP
 #    IP address clamd will listen on: change to localhost

 #    OK, restart your computer and open Thunderbird. Restarting will load clamav with the new settings and update the virus database.

 #    Tools -> Add-ons -> clamdrib -> Preferences -> Test Settings this will mconfirm everything is working.

 #    Done.

sudo freshclam
sudo clamscan -r --bell -i /

#user scan
#clamscan -r --bell -i ./

#checking daemon
ps ax | grep [c]lamd

#reporting
sudo clamscan -r /folder/to/scan/ | grep FOUND >> /path/to/save/report/file.txt 

# kill anything that has to do with printing!
sudo aptitude remove cups

#https://wiki.ubuntu.com/UncomplicatedFirewall
#paranoid firewall settings
sudo ufw enable
sudo ufw logging on
sudo ufw delete CUPS

