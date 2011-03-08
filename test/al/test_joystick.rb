$: << '.'
$: << 'test/al'

require 'test_al_helper'

assert { Al.init                   }
assert { Al::Joystick              }
assert { !Al::Joystick.init?       } 
assert { Al::Joystick.init         }
assert { Al::Joystick.init?        }
assert { Al::Joystick.amount       }
assert { !Al::Joystick.reconfigure }

# can only test rest if joystick is available. 
if Al::Joystick.amount > 0
  js = nil 
  assert { js = js.get(0)                 }
  assert { js.class == Al::Joystick       }
  assert { js.sticks                      }
  assert { js.buttons                     }
  assert { js.axes(0)                     }
  assert { js.name                        }
  assert { js.button_name(0)              }
  assert { js.stick_name(0)               }
  assert { js.axis_name(0, 0)             }
  sta = nil
  assert { sta = js.state                 }
  assert { sta.class == Al::JoystickState } 
  assert { sta.button(0)                  }
  assert { sta.axis(0, 0)                 }
end 


assert { Al::Joystick.done          }
assert { !Al::Joystick.init?        }


