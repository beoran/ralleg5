$: << '.'
$: << 'test/al'

require 'test_al_helper'

assert { Al.init }
assert { Al::Mode } 
assert { Al::Mode.amount > 0 }
Al::Mode.amount
mode = nil
assert { mode = Al::Mode.get(0) }
assert { mode.width  > 0 } 
assert { mode.height > 0 }
assert { mode.format     }
assert { mode.rate       }
# p mode.width, mode.height, mode.format, mode.rate



