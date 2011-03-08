$: << '.'
$: << 'test/al'

require 'test_al_helper'

assert { Al.init                        }
assert { Al::Keyboard                   }
assert { !Al::Keyboard.init?            }
assert { Al::Keyboard.init              }
assert { Al::Keyboard.init?             }

assert { Al::Key                         }
assert { Al::Key::KEY_A                  }

include Al::Key

assert { KEY_A                           }
assert { KEY_A == 1                      }
assert { KEYMOD_SHIFT                    }

assert { Al::Keyboard.keyname(KEY_A) == "a" }
assert { !(Al::Keyboard.down?(KEY_A).nil?)  }
assert { Al::Keyboard.keyname(-1).nil?      }
assert { Al::Keyboard.keyname(1234567).nil? }

assert { Al::Keyboard.done              }
assert { !Al::Keyboard.init?            }



