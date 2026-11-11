QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEditor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp mainwindow.cpp aboutdialog.cpp finddialog.cpp replacedialog.cpp

HEADERS += mainwindow.h aboutdialog.h finddialog.h replacedialog.h

FORMS += mainwindow.ui aboutdialog.ui finddialog.ui replacedialog.ui
