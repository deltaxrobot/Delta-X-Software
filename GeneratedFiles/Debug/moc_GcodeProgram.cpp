/****************************************************************************
** Meta object code from reading C++ file 'GcodeProgram.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GcodeProgram.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GcodeProgram.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GcodeProgram_t {
    QByteArrayData data[8];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GcodeProgram_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GcodeProgram_t qt_meta_stringdata_GcodeProgram = {
    {
QT_MOC_LITERAL(0, 0, 12), // "GcodeProgram"
QT_MOC_LITERAL(1, 13, 8), // "Selected"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "GcodeProgram*"
QT_MOC_LITERAL(4, 37, 3), // "ptr"
QT_MOC_LITERAL(5, 41, 7), // "Deleted"
QT_MOC_LITERAL(6, 49, 16), // "SelectNewProgram"
QT_MOC_LITERAL(7, 66, 13) // "DeleteProgram"

    },
    "GcodeProgram\0Selected\0\0GcodeProgram*\0"
    "ptr\0Deleted\0SelectNewProgram\0DeleteProgram"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GcodeProgram[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   40,    2, 0x0a /* Public */,
       7,    0,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GcodeProgram::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GcodeProgram *_t = static_cast<GcodeProgram *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Selected((*reinterpret_cast< GcodeProgram*(*)>(_a[1]))); break;
        case 1: _t->Deleted((*reinterpret_cast< GcodeProgram*(*)>(_a[1]))); break;
        case 2: _t->SelectNewProgram(); break;
        case 3: _t->DeleteProgram(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GcodeProgram* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GcodeProgram* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GcodeProgram::*_t)(GcodeProgram * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgram::Selected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GcodeProgram::*_t)(GcodeProgram * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgram::Deleted)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GcodeProgram::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GcodeProgram.data,
      qt_meta_data_GcodeProgram,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GcodeProgram::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GcodeProgram::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GcodeProgram.stringdata0))
        return static_cast<void*>(const_cast< GcodeProgram*>(this));
    return QObject::qt_metacast(_clname);
}

int GcodeProgram::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GcodeProgram::Selected(GcodeProgram * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GcodeProgram::Deleted(GcodeProgram * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
