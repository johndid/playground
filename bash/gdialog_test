#!/bin/sh

#!/bin/sh

if zenity --entry \
--title="cntlm windows proxy sonnection setup" \
--text="Enter your windows user name:" \
--entry-text ""
  then user=$?
  else echo "Missing user name"
fi

if zenity --entry \
--title="cntlm windows proxy sonnection setup" \
--text="Enter your windows password:" \
--entry-text "" \
--hide-text
  then passwd=$?
  else echo "Missing password"
fi

echo "$user:$passwd"

# ENTRY=`zenity --title "Windows proxy setup" --password --username`

# case $? in
#          0)
# 	 	echo "User Name: `echo $ENTRY | cut -d'|' -f1`"
# 	 	echo "Password : `echo $ENTRY | cut -d'|' -f2`"
# 		;;
#          1)
#                 echo "Stop login.";;
#         -1)
#                 echo "An unexpected error has occurred.";;
# esac
