# -*- coding: utf-8 -*-
import io

p = r'D:\samp2_4App\qwmainwind.ui'
s = io.open(p, encoding='utf-8').read()

# 1) 菜单栏：在"格式"菜单后增加"帮助"菜单
old = '''   <widget class="QMenu" name="menu_3">
    <property name="title">
     <string>格式</string>
    </property>
    <addaction name="actFontBold"/>
    <addaction name="actFontItalic"/>
    <addaction name="actFontUnder"/>
    <addaction name="separator"/>
    <addaction name="actToolbarLab"/>
   </widget>
   <addaction name="menu"/>
   <addaction name="menu_2"/>
   <addaction name="menu_3"/>
  </widget>'''
new = '''   <widget class="QMenu" name="menu_3">
    <property name="title">
     <string>格式</string>
    </property>
    <addaction name="actFontBold"/>
    <addaction name="actFontItalic"/>
    <addaction name="actFontUnder"/>
    <addaction name="separator"/>
    <addaction name="actToolbarLab"/>
   </widget>
   <widget class="QMenu" name="menu_4">
    <property name="title">
     <string>帮助</string>
    </property>
    <addaction name="actAbout"/>
   </widget>
   <addaction name="menu"/>
   <addaction name="menu_2"/>
   <addaction name="menu_3"/>
   <addaction name="menu_4"/>
  </widget>'''
assert s.count(old) == 1, 'menu block not found: %d' % s.count(old)
s = s.replace(old, new)

# 2) 工具栏：在 actNew 之后增加 actAbout
old2 = '''   <addaction name="actNew"/>
   <addaction name="actOpen"/>'''
new2 = '''   <addaction name="actNew"/>
   <addaction name="actAbout"/>
   <addaction name="actOpen"/>'''
assert s.count(old2) == 1, 'toolbar block not found: %d' % s.count(old2)
s = s.replace(old2, new2)

# 3) 添加 actAbout action 定义（插在 actNew 定义之前）
old3 = '''  <action name="actNew">'''
new3 = '''  <action name="actAbout">
   <property name="icon">
    <iconset resource="res.qrc">
     <normaloff>:/images/images/about.bmp</normaloff>:/images/images/about.bmp</iconset>
   </property>
   <property name="text">
    <string>关于</string>
   </property>
   <property name="toolTip">
    <string>关于</string>
   </property>
  </action>
  <action name="actNew">'''
assert s.count(old3) == 1, 'actNew not found: %d' % s.count(old3)
s = s.replace(old3, new3)

io.open(p, 'w', encoding='utf-8', newline='\n').write(s)
print('UI updated OK')
