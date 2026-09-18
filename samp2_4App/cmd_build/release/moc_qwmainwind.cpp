/****************************************************************************
** Meta object code from reading C++ file 'qwmainwind.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qwmainwind.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwmainwind.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QWMainWind_t {
    QByteArrayData data[18];
    char stringdata0[344];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QWMainWind_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QWMainWind_t qt_meta_stringdata_QWMainWind = {
    {
QT_MOC_LITERAL(0, 0, 10), // "QWMainWind"
QT_MOC_LITERAL(1, 11, 24), // "on_actFontBold_triggered"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 7), // "checked"
QT_MOC_LITERAL(4, 45, 26), // "on_actFontItalic_triggered"
QT_MOC_LITERAL(5, 72, 25), // "on_actFontUnder_triggered"
QT_MOC_LITERAL(6, 98, 19), // "on_actNew_triggered"
QT_MOC_LITERAL(7, 118, 20), // "on_actOpen_triggered"
QT_MOC_LITERAL(8, 139, 21), // "on_actAbout_triggered"
QT_MOC_LITERAL(9, 161, 20), // "on_actFont_triggered"
QT_MOC_LITERAL(10, 182, 27), // "on_txtEdit_selectionChanged"
QT_MOC_LITERAL(11, 210, 24), // "on_txtEdit_copyAvailable"
QT_MOC_LITERAL(12, 235, 1), // "b"
QT_MOC_LITERAL(13, 237, 26), // "on_actToolbarLab_triggered"
QT_MOC_LITERAL(14, 264, 31), // "on_spinBoxFontSize_valueChanged"
QT_MOC_LITERAL(15, 296, 9), // "aFontSize"
QT_MOC_LITERAL(16, 306, 32), // "on_comboFont_currentIndexChanged"
QT_MOC_LITERAL(17, 339, 4) // "arg1"

    },
    "QWMainWind\0on_actFontBold_triggered\0"
    "\0checked\0on_actFontItalic_triggered\0"
    "on_actFontUnder_triggered\0on_actNew_triggered\0"
    "on_actOpen_triggered\0on_actAbout_triggered\0"
    "on_actFont_triggered\0on_txtEdit_selectionChanged\0"
    "on_txtEdit_copyAvailable\0b\0"
    "on_actToolbarLab_triggered\0"
    "on_spinBoxFontSize_valueChanged\0"
    "aFontSize\0on_comboFont_currentIndexChanged\0"
    "arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QWMainWind[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       4,    1,   77,    2, 0x08 /* Private */,
       5,    1,   80,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    1,   88,    2, 0x08 /* Private */,
      13,    1,   91,    2, 0x08 /* Private */,
      14,    1,   94,    2, 0x08 /* Private */,
      16,    1,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void QWMainWind::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QWMainWind *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actFontBold_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_actFontItalic_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_actFontUnder_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_actNew_triggered(); break;
        case 4: _t->on_actOpen_triggered(); break;
        case 5: _t->on_actAbout_triggered(); break;
        case 6: _t->on_actFont_triggered(); break;
        case 7: _t->on_txtEdit_selectionChanged(); break;
        case 8: _t->on_txtEdit_copyAvailable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_actToolbarLab_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_spinBoxFontSize_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_comboFont_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QWMainWind::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_QWMainWind.data,
    qt_meta_data_QWMainWind,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QWMainWind::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QWMainWind::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QWMainWind.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QWMainWind::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
