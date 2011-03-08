$: << '.'
$: << 'test/al'

require 'test_al_helper'

assert { Al.init }
assert { Al::Event       }
assert { Al::EventQueue  }
assert { Al::EventSource }

queue = nil
assert { queue = Al::EventQueue.new } 
assert { queue.empty? }
assert { !queue.peek }
assert { !queue.poll }
assert { !queue.timeout(0.1) }

Al::Display.flags = Al::Display::WINDOWED
disp = Al::Display.create(640, 480)
assert { disp } 
esrc = disp.eventsource
assert { esrc } 
assert { esrc.class == Al::EventSource }
assert { queue.register(esrc) } 
# Below is an interactive test. 
# assert { queue.timeout(10.0) }
# ev = queue.poll
# assert { ev }
# assert { ev.type ==  }

disp.destroy



