$: << '.'
$: << 'test/al'

require 'test_al_helper'

 
assert { Al.init }

assert { Al::Display }
assert { Al::Display.flags }
assert { Al::Display.rate }
p Al::Display.flags
assert { Al::Display.flags = (Al::Display.flags & Al::Display::OPENGL) }
p Al::Display.flags 
assert { Al::Display.flags & Al::Display::OPENGL != 0 }

assert { Al::Display::SINGLE_BUFFER }
p Al::Display.option(Al::Display::SINGLE_BUFFER) 
assert { Al::Display.option(Al::Display::SINGLE_BUFFER) }
assert { Al::Display.option_set(Al::Display::SINGLE_BUFFER, 1, nil) } 
assert { Al::Display.option(Al::Display::SINGLE_BUFFER) == 1 }
 
disp = nil
assert { disp = Al::Display.create(640, 480) }
assert { disp.width                 }
assert { disp.height                }
assert { disp.format                }
assert { disp.rate                  }
assert { disp.flags                 }
assert { !disp.destroy?             }
p  disp.width, disp.height, disp.format, disp.rate, disp.flags
 
assert { Al::Display.flip } 
assert { Al::Display.vsync }
assert { Al::Display.update_region(0,0,1,1) }
# Deferred drawing
assert { ! Al::Display.defer? }
assert { Al::Display.defer!(true) }
assert { Al::Display.defer? } 
assert { !Al::Display.defer!(false) }
assert { ! Al::Display.defer? }

# Setting the window's position 
assert { disp.position_set(100, 200) }
p disp.position
sleep 0.5
assert { disp.position == [100, 200] }
# Note: position_set(0,0) may fail if Allegro or the WM refuse to position there.
assert { disp.position_set(10, 25) }
sleep 0.5
assert { disp.position == [10, 25] }
p disp.position

assert { disp.resize(10, 20) }  
assert { disp.width == 10 }
assert { disp.resize(640, 480) }
disp.title="ralleg5"

curr = nil 
assert { curr = Al::Display.current }
assert { disp.width   == curr.width }
assert { disp.height  == curr.height}
assert { disp.format  == curr.format}
assert { disp.rate    == curr.rate  }
assert { disp.flags   == curr.flags }
assert { Al::Display::FULLSCREEN_WINDOW } 
assert { disp.flags & Al::Display::FULLSCREEN_WINDOW == 0 }
disp.toggle_flag(Al::Display::FULLSCREEN_WINDOW, true)
assert { disp.flags & Al::Display::FULLSCREEN_WINDOW != 0 }
disp.toggle_flag(Al::Display::FULLSCREEN_WINDOW, false)
assert { disp.flags & Al::Display::FULLSCREEN_WINDOW == 0 }




assert { disp.destroy   }
assert { disp.destroy?  }
assert { GC.start || true } 
