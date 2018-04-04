proc createGUI { } {
  set frame .frame

  frame $frame

  #----

  global asteroids

  set asteroids $frame.asteroids

  CTclAsteroidsCanvas $asteroids -width 800 -height 600

  pack $asteroids -side top -anchor w -fill both -expand true

  focus $asteroids

  #----

  pack $frame -side left -fill both -expand true

  #----

  after 16 timeout
}

proc timeout { } {
  global asteroids

  $asteroids timeout

  after 16 timeout
}

createGUI
