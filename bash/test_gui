#!/usr/bin/wish

set cntlm_cntl "/usr/sbin/cntlm"
global cntlm_cntl

proc start {} {
  global cntlm_cntl
  exec $cntlm_cntl start & 
}

proc stop {} {
  global cntlm_cntl
  exec $cntlm_cntl stop &
}

proc restart {} {
  global cntlm_cntl
  exec $cntlm_cntl restart &
}

proc screen {} {
  frame .top -borderwidth 10
  pack .top -fill x	
  button .top.start -text "Start" -command start
  button .top.stop -text "Stop" -command stop
  button .top.restart -text "Restart" -command restart
  pack .top.start .top.stop .top.restart -side left -padx 0p -pady 0
}

screen
