/****************************************************************************
** Meta object code from reading C++ file 'hsvwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../hsvwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hsvwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HSVWindow_t {
    QByteArrayData data[11];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HSVWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HSVWindow_t qt_meta_stringdata_HSVWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "HSVWindow"
QT_MOC_LITERAL(1, 10, 12), // "ValueChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "minH"
QT_MOC_LITERAL(4, 29, 4), // "maxH"
QT_MOC_LITERAL(5, 34, 4), // "minS"
QT_MOC_LITERAL(6, 39, 4), // "maxS"
QT_MOC_LITERAL(7, 44, 4), // "minV"
QT_MOC_LITERAL(8, 49, 4), // "maxV"
QT_MOC_LITERAL(9, 54, 9), // "threshold"
QT_MOC_LITERAL(10, 64, 24) // "UpdateSliderValueToLabel"

    },
    "HSVWindow\0ValueChanged\0\0minH\0maxH\0"
    "minS\0maxS\0minV\0maxV\0threshold\0"
    "UpdateSliderValueToLabel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HSVWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    6,   29,    2, 0x06 /* Public */,
       1,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::Int,    9,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void HSVWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HSVWindow *_t = static_cast<HSVWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ValueChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 1: _t->ValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->UpdateSliderValueToLabel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HSVWindow::*_t)(int , int , int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HSVWindow::ValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (HSVWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HSVWindow::ValueChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject HSVWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_HSVWindow.data,
      qt_meta_data_HSVWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HSVWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HSVWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HSVWindow.stringdata0))
        return static_cast<void*>(const_cast< HSVWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int HSVWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void HSVWindow::ValueChanged(int _t1, int _t2, int _t3, int _t4, int _t5, int _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HSVWindow::ValueChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
