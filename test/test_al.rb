$: << '.'
$: << '..'
$: << '../lib'
$: << 'lib'
$: << 'ext/ralleg5'
$: << '../ext/ralleg5'

require 'test_helper'
require 'ralleg5.so' 

assert { Al } 
assert { !Al.install? } 
assert { Al.init } 
assert { Al.install?  } 
assert { Al.uninstall.nil? } 
assert { !Al.install? } 


