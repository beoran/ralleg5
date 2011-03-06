$: << '.'
$: << '..'
$: << '../..'
$: << '../../lib'
$: << '../lib'
$: << 'lib'
$: << 'ext/ralleg5'
$: << '../ext/ralleg5'
$: << '../../ext/ralleg5'

require 'test_helper'
require 'ralleg5.so' 

assert { Al::Display } 
assert { Al.init } 
disp = nil
assert { disp = Al::Display.create(640, 480) } 



