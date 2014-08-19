import sys
import re

new_sys_path = []
for item in sys.path:
    if  (not re.match(r'.*jiltoxmi-\d+.\d+dev-py\d+.\d+.egg$', item)
        and not re.match(r'.*xmi-\d+.\d+dev-py\d+.\d+.egg$', item)):
        new_sys_path.append(item)

new_sys_path.append('C:\\cygwin\\usr\\local\\lib\\python2.4\\Lib\\site-packages\\eggs\\jiltoxmi')
new_sys_path.append('C:\\cygwin\\usr\\local\\lib\\python2.4\\Lib\\site-packages\\eggs\\xmi')

sys.path = new_sys_path

AAPLDirectory = 'D:\BGM\Arch\SourceForAnalysis'

from XmiGen.AutosarGen import AutosarAPLGen

gen = AutosarAPLGen(AAPLDirectory)
gen.xmize()
