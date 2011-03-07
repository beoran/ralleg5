$: << '.'
$: << 'test/al'

require 'test_al_helper'

assert { Al.init }
assert { Al::Monitor }
assert { Al::Monitor.amount > 0 }

# Currently active monitor.
assert { Al::Monitor.active }
assert { Al::Monitor::DEFAULT   }
assert { Al::Monitor.active == Al::Monitor::DEFAULT }
assert { Al::Monitor.active = 0 }
assert { Al::Monitor.active == 0 }
assert { Al::Monitor.active = Al::Monitor::DEFAULT }
assert { Al::Monitor.active == Al::Monitor::DEFAULT }

# getting the monitor information
monitor = nil
assert { monitor = Al::Monitor.get(Al::Monitor::DEFAULT) }
assert { monitor.x1      }
assert { monitor.y1      }
assert { monitor.x2 > monitor.x1  }
assert { monitor.y2 > monitor.y1  } 
 

 
