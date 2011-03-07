$: << '.'
$: << 'test/al'

require 'test_al_helper'

assert { Al.init }
assert { Al::Color }

col1 = nil 
assert { col1 = Al::Color.rgb(1, 2, 3) }
col2 = nil
assert { col2 = Al::Color.rgba(10, 20, 30, 40) } 
assert { col1.rgb  == [1,2,3]       } 
assert { col1.rgba == [1,2,3,255]   }
assert { col2.rgb  == [10,20,30]    } 
assert { col2.rgba == [10,20,30,40] }




