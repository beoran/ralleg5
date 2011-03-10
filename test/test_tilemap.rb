$: << '.'
$: << 'test/al'

require 'test_al_helper'


assert { Al.init }
assert { Al::Bitmap.init }
assert { Al::Display.flags = Al::Display::WINDOWED } 
@disp = nil
assert { @disp = Al::Display.create(640, 480) }
DATA_DIR = [ 'data' ]

@bm1 = Al::Bitmap.load(File.join(*DATA_DIR, 'tile_aqua.png'));
@bm2 = Al::Bitmap.load(File.join(*DATA_DIR, 'tile_grass.png'));
assert { @bm1 } 
assert { @bm2 }

start = Time.now
10.times do 
  dx = 0  
  for x in (0...20)
    dy = 0
    for y in (0..15)
      @bm1.draw(dx, dy, 0)
      dy += 32
    end
    dx += 32
  end
  Al::Display.flip
end
stop = Time.now
delta = stop - start 
p delta, 10.0 / delta
p @bm1.compatible?

# I'm getting a smooth 9 frames per second on an older PC under Linux with no HW 
# accelleration... that kind of sucks. Alllegro 5 doesn't seem to have a 
# software fallback with acceptable speed. Not to menton instability of the 
# screen... 

sleep(1) 

















