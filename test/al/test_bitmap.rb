$: << '.'
$: << 'test/al'

require 'test_al_helper'

assert { Al.init }
assert { Al::Bitmap.init }

assert { Al::Bitmap }
assert { Al::Bitmap.flags }
assert { Al::Bitmap.flags & Al::Bitmap::MEMORY_BITMAP == 0 }
assert { Al::Bitmap.flags |= Al::Bitmap::MEMORY_BITMAP }
assert { Al::Bitmap.flags & Al::Bitmap::MEMORY_BITMAP != 0 }
assert { Al::Bitmap.format }
assert { Al::Bitmap.format =  Al::Bitmap::FORMAT_ANY_WITH_ALPHA }
assert { Al::Bitmap.format == Al::Bitmap::FORMAT_ANY_WITH_ALPHA }

assert {  Al::Bitmap.blender }
assert {  Al::Bitmap.blender.size == 3 } 
assert {  Al::Bitmap.alphablender }
assert {  Al::Bitmap.alphablender.size == 6}

bm = nil
assert { bm = Al::Bitmap.new(32, 64) } 
assert { bm.width  == 32 } 
assert { bm.height == 64 }
assert { bm.format }
p bm.format
# bm.format may be different from Al::Bitmap.format, so no test for this
assert { (bm.format == Al::Bitmap.format) || (bm.format != Al::Bitmap.format) }
assert { bm.flags }
assert { bm.flags == Al::Bitmap.flags }
p bm.flags
p 

assert { Al::Lock } 
assert { !bm.lock? } 
lo = nil
assert { lo = bm.lock!(0, 0)} 
assert { lo.format } 
assert { lo.pixelsize } 
assert { lo.pitch } 
assert { lo.class == Al::Lock } 
assert { bm.lock? } 
assert { bm.unlock! } 
assert { !bm.lock? } 

assert { bm.target! }
assert { Al::Display.clear_to(Al::Color.rgb(0, 128, 128))       }
assert { Al::Bitmap.putpixel(10, 20, Al::Color.rgb(128, 0, 0))  }
assert { bm.getpixel(0, 0).rgb   == [  0, 128, 128]             }
assert { bm.getpixel(10, 20).rgb == [128,   0,   0]             }
outname = File.join("test", "output", "test_bitmap.png")
assert { bm.save(outname)}

bm2 = nil
assert { bm2 = Al::Bitmap.load(outname) }
assert { bm2.width  == bm.width }
assert { bm2.height == bm.height }
assert { bm2.getpixel(0, 0).rgb   == [  0, 128, 128]             }
assert { bm2.getpixel(10, 20).rgb == [128,   0,   0]             }




bm = nil
assert { !GC.start } 

