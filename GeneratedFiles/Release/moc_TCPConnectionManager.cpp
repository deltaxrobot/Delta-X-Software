/****************************************************************************
** Meta object code from reading C++ file 'TCPConnectionManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TCPConnectionManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TCPConnectionManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TCPConnectionManager_t {
    QByteArrayData data[16];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TCPConnectionManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TCPConnectionManager_t qt_meta_stringdata_TCPConnectionManager = {
    {
QT_MOC_LITERAL(0, 0, 20), // "TCPConnectionManager"
QT_MOC_LITERAL(1, 21, 28), // "ReceiveVariableChangeCommand"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 4), // "name"
QT_MOC_LITERAL(4, 56, 5), // "value"
QT_MOC_LITERAL(5, 62, 28), // "ReceivePositionUpdateCommand"
QT_MOC_LITERAL(6, 91, 1), // "x"
QT_MOC_LITERAL(7, 93, 1), // "y"
QT_MOC_LITERAL(8, 95, 1), // "z"
QT_MOC_LITERAL(9, 97, 1), // "w"
QT_MOC_LITERAL(10, 99, 9), // "ReceiveOk"
QT_MOC_LITERAL(11, 109, 15), // "ReceivePosition"
QT_MOC_LITERAL(12, 125, 18), // "CreatNewConnection"
QT_MOC_LITERAL(13, 144, 19), // "ReadDataFromClients"
QT_MOC_LITERAL(14, 164, 16), // "SendMessageToAll"
QT_MOC_LITERAL(15, 181, 3) // "msg"

    },
    "TCPConnectionManager\0ReceiveVariableChangeCommand\0"
    "\0name\0value\0ReceivePositionUpdateCommand\0"
    "x\0y\0z\0w\0ReceiveOk\0ReceivePosition\0"
    "CreatNewConnection\0ReadDataFromClients\0"
    "SendMessageToAll\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TCPConnectionManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       5,    4,   54,    2, 0x06 /* Public */,
      10,    0,   63,    2, 0x06 /* Public */,
      11,    4,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   73,    2, 0x0a /* Public */,
      13,    0,   74,    2, 0x0a /* Public */,
      14,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Float,    3,    4,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    6,    7,    8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    6,    7,    8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,

       0        // eod
};

void TCPConnectionManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TCPConnectionManager *_t = static_cast<TCPConnectionManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ReceiveVariableChangeCommand((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: _t->ReceivePositionUpdateCommand((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 2: _t->ReceiveOk(); break;
        case 3: _t->ReceivePosition((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 4: _t->CreatNewConnection(); break;
        case 5: _t->ReadDataFromClients(); break;
        case 6: _t->SendMessageToAll((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TCPConnectionManager::*_t)(QString , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPConnectionManager::ReceiveVariableChangeCommand)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TCPConnectionManager::*_t)(float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPConnectionManager::ReceivePositionUpdateCommand)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TCPConnectionManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPConnectionManager::ReceiveOk)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TCPConnectionManager::*_t)(float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPConnectionManager::ReceivePosition)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TCPConnectionManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TCPConnectionManager.data,
      qt_meta_data_TCPConnectionManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TCPConnectionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCPConnectionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TCPConnectionManager.stringdata0))
        return static_cast<void*>(const_cast< TCPConnectionManager*>(this));
    return QObject::qt_metacast(_clname);
}

int TCPConnectionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TCPConnectionManager::ReceiveVariableChangeCommand(QString _t1, float _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TCPConnectionManager::ReceivePositionUpdateCommand(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TCPConnectionManager::ReceiveOk()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void TCPConnectionManager::ReceivePosition(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
