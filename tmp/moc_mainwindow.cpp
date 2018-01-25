/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_datamange_t {
    QByteArrayData data[4];
    char stringdata0[30];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_datamange_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_datamange_t qt_meta_stringdata_datamange = {
    {
QT_MOC_LITERAL(0, 0, 9), // "datamange"
QT_MOC_LITERAL(1, 10, 15), // "on_labelrefresh"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 2) // "ID"

    },
    "datamange\0on_labelrefresh\0\0ID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_datamange[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void datamange::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        datamange *_t = static_cast<datamange *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_labelrefresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject datamange::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_datamange.data,
      qt_meta_data_datamange,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *datamange::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *datamange::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_datamange.stringdata0))
        return static_cast<void*>(const_cast< datamange*>(this));
    return QObject::qt_metacast(_clname);
}

int datamange::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[12];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "on_systemset"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 17), // "on_settingchanged"
QT_MOC_LITERAL(4, 43, 3), // "str"
QT_MOC_LITERAL(5, 47, 21), // "on_onethread_finished"
QT_MOC_LITERAL(6, 69, 4), // "tmpi"
QT_MOC_LITERAL(7, 74, 19), // "on_BTencypt_clicked"
QT_MOC_LITERAL(8, 94, 19), // "on_BTdecypt_clicked"
QT_MOC_LITERAL(9, 114, 18), // "on_BTpause_clicked"
QT_MOC_LITERAL(10, 133, 21), // "on_BTcontinue_clicked"
QT_MOC_LITERAL(11, 155, 19) // "on_BTimport_clicked"

    },
    "MainWindow\0on_systemset\0\0on_settingchanged\0"
    "str\0on_onethread_finished\0tmpi\0"
    "on_BTencypt_clicked\0on_BTdecypt_clicked\0"
    "on_BTpause_clicked\0on_BTcontinue_clicked\0"
    "on_BTimport_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    1,   55,    2, 0x08 /* Private */,
       5,    1,   58,    2, 0x08 /* Private */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    0,   63,    2, 0x08 /* Private */,
      10,    0,   64,    2, 0x08 /* Private */,
      11,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_systemset(); break;
        case 1: _t->on_settingchanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_onethread_finished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_BTencypt_clicked(); break;
        case 4: _t->on_BTdecypt_clicked(); break;
        case 5: _t->on_BTpause_clicked(); break;
        case 6: _t->on_BTcontinue_clicked(); break;
        case 7: _t->on_BTimport_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
