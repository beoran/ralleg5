$: << '.'
$: << 'test/al'

require 'test_al_helper'

 
assert { Al.init }
assert { Al::Display }
assert { Al::Draw }
assert { Al::Draw.init }
assert { Al::Bitmap.init }

bm = Al::Bitmap.new(640, 480) 
bm.target!

disp = nil
assert { Al::Display.flags = Al::Display::WINDOWED } 
assert { disp = Al::Display.create(640, 480) }
include Al::Draw
blue   = Al::Color.rgb(0,0,255)
yellow = Al::Color.rgb(255, 255, 0)
Al::Display.clear_to(blue) 
assert { Al::Draw.draw_rectangle(10, 20, 50, 70, yellow, 5); }


Al::Display.flip
sleep(3)




