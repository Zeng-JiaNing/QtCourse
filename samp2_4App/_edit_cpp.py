# -*- coding: utf-8 -*-
import io

p = r'D:\samp2_4App\qwmainwind.cpp'
s = io.open(p, encoding='utf-8').read()

# 添加 QMessageBox 头文件
old_inc = '''#include    <QCoreApplication>
#include    <Qlabel>
#include    <QTextCharFormat>'''
new_inc = '''#include    <QCoreApplication>
#include    <Qlabel>
#include    <QTextCharFormat>
#include    <QMessageBox>'''
assert s.count(old_inc) == 1, 'cpp include block not found'
s = s.replace(old_inc, new_inc)

# 在 on_actNew_triggered 前插入 on_actAbout_triggered 实现
old_impl = '''void QWMainWind::on_actNew_triggered()
{//新建文件'''
new_impl = '''void QWMainWind::on_actAbout_triggered()
{//关于窗口，显示姓名、学号等个人信息
    QMessageBox::about(this, tr("关于"),
        tr("<h2>samp2_4</h2>"
           "<p>开发人员信息：</p>"
           "<p>姓名：__NAME__</p>"
           "<p>学号：__ID__</p>"));
}

void QWMainWind::on_actNew_triggered()
{//新建文件'''
assert s.count(old_impl) == 1, 'cpp new impl block not found'
s = s.replace(old_impl, new_impl)

io.open(p, 'w', encoding='utf-8', newline='\n').write(s)
print('qwmainwind.cpp updated OK')
