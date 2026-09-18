# -*- coding: utf-8 -*-
import io

p = r'D:\samp2_4App\res.qrc'
s = io.open(p, encoding='utf-8').read()

old = '''        <file>images/new2.bmp</file>'''
new = '''        <file>images/new2.bmp</file>
        <file>images/about.bmp</file>'''
assert s.count(old) == 1, 'res.qrc new2 not found'
s = s.replace(old, new)
io.open(p, 'w', encoding='utf-8', newline='\n').write(s)
print('res.qrc updated OK')
