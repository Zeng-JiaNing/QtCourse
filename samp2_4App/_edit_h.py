# -*- coding: utf-8 -*-
import io

p = r'D:\samp2_4App\qwmainwind.h'
s = io.open(p, encoding='utf-8').read()

old = '''    void on_actNew_triggered();//新建文件
    void on_actOpen_triggered();//打开文件'''
new = '''    void on_actNew_triggered();//新建文件
    void on_actOpen_triggered();//打开文件

    void on_actAbout_triggered();//关于窗口'''
assert s.count(old) == 1, 'h slots block not found'
s = s.replace(old, new)
io.open(p, 'w', encoding='utf-8', newline='\n').write(s)
print('qwmainwind.h updated OK')
