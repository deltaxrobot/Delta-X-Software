/****************************************************************************
** Meta object code from reading C++ file 'BlobManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BlobManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BlobManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BlobManager_t {
    QByteArrayData data[10];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BlobManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BlobManager_t qt_meta_stringdata_BlobManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "BlobManager"
QT_MOC_LITERAL(1, 12, 23), // "NewUpdateObjectPosition"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 4), // "name"
QT_MOC_LITERAL(4, 42, 5), // "value"
QT_MOC_LITERAL(5, 48, 24), // "UpdateNewPositionObjects"
QT_MOC_LITERAL(6, 73, 6), // "deltaX"
QT_MOC_LITERAL(7, 80, 6), // "deltaY"
QT_MOC_LITERAL(8, 87, 18), // "RemoveOldestObject"
QT_MOC_LITERAL(9, 106, 22) // "RemoveAllDetectObjects"

    },
    "BlobManager\0NewUpdateObjectPosition\0"
    "\0name\0value\0UpdateNewPositionObjects\0"
    "deltaX\0deltaY\0RemoveOldestObject\0"
    "RemoveAllDetectObjects"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BlobManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   39,    2, 0x0a /* Public */,
       8,    0,   44,    2, 0x0a /* Public */,
       9,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Float,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BlobManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BlobManager *_t = static_cast<BlobManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->NewUpdateObjectPosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->UpdateNewPositionObjects((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 2: _t->RemoveOldestObject(); break;
        case 3: _t->RemoveAllDetectObjects(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BlobManager::*_t)(QString , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BlobManager::NewUpdateObjectPosition)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject BlobManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BlobManager.data,
      qt_meta_data_BlobManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BlobManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BlobManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BlobManager.stringdata0))
        return static_cast<void*>(const_cast< BlobManager*>(this));
    return QObject::qt_metacast(_clname);
}

int BlobManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void BlobManager::NewUpdateObjectPosition(QString _t1, float _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
