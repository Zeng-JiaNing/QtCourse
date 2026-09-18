# -*- coding: utf-8 -*-
import io, re
s = io.open(r'D:\samp2_4App\qwmainwind.ui', encoding='utf-8').read()
print('actAbout count:', s.count('actAbout'))
m = re.search(r'<widget class="QToolBar" name="mainToolBar">.*?</widget>', s, re.S)
print(m.group(0) if m else 'toolbar not found')
