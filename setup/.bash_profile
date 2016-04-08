# .bash_profile for cannabissen
# Notice that this setup requires MacPorts to be installed! Perhaps ports should somehow be checked prior to run
# But I'm confidend i remembered to install it
############################################################
export CLICOLOR=1
export LSCOLORS=ExFxBxDxCxegedabagacad
export GREP_OPTIONS='--color=auto'
export DISPLAY="localhost:0.0"
export LC_ALL="en_GB.UTF-8"

# The following sets up a local user bin/ directory, that points to the github playground database
# Then it includes the airport utility, needed for the wifi alias below
[ ! -L bin ] && ln -s /Users/$USER/Documents/src/playground/bash bin/
[ ! -L /Users/$USER/bin/airport ] && ln -s /System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport /Users/$USER/bin/airport

# Setup paths
export PATH="/Users/$USER/bin:/opt/local/bin:/opt/local/sbin:/usr/local/bin:/usr/local/mysql/bin:$PATH"
export MANPATH=/opt/local/share/man:$MANPATH

# Setup terminal promot to: user@host:~/$ 
export PS1="\[\033[36m\]\u\[\033[m\]@\[\033[32m\]\h:\[\033[33;1m\]\w\[\033[m\]/$ "

# Adding tab completion for MacPorts
if [ -f /opt/local/etc/profile.d/bash_completion.sh ]; then
      . /opt/local/etc/profile.d/bash_completion.sh
fi

# Various alias commands
alias curl="curl -O"
alias established="lsof -i | grep ESTABLISHED"
alias listen="lsof -i | grep LISTEN"
alias connected="lsof -i | grep CONNECTED"
alias update="sudo softwareupdate -i -a"
alias lswifi="airport -s"
alias shred="gshred"

# install tree unix command using port, it accepts directory arguments
#alias filetree="ls -R | grep ":$" | sed -e 's/:$//' -e 's/[^-][^\/]*\//--/g' -e 's/^/ /' -e 's/-/|/'"

# Congrats champ setup is complete, here's your cookie.
text=$(fortune)
echo $text && say $text
