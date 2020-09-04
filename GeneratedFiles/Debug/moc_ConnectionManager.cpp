/****************************************************************************
** Meta object code from reading C++ file 'ConnectionManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ConnectionManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConnectionManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectionManager_t {
    QByteArrayData data[27];
    char stringdata0[344];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionManager_t qt_meta_stringdata_ConnectionManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ConnectionManager"
QT_MOC_LITERAL(1, 18, 14), // "FinishReadLine"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 3), // "msg"
QT_MOC_LITERAL(4, 38, 23), // "ExternalMCUTransmitText"
QT_MOC_LITERAL(5, 62, 4), // "text"
QT_MOC_LITERAL(6, 67, 17), // "DeltaResponeReady"
QT_MOC_LITERAL(7, 85, 21), // "DeltaResponeGcodeDone"
QT_MOC_LITERAL(8, 107, 14), // "InHomePosition"
QT_MOC_LITERAL(9, 122, 1), // "x"
QT_MOC_LITERAL(10, 124, 1), // "y"
QT_MOC_LITERAL(11, 126, 1), // "z"
QT_MOC_LITERAL(12, 128, 1), // "w"
QT_MOC_LITERAL(13, 130, 24), // "ReceiveConvenyorPosition"
QT_MOC_LITERAL(14, 155, 28), // "ReceiveVariableChangeCommand"
QT_MOC_LITERAL(15, 184, 4), // "name"
QT_MOC_LITERAL(16, 189, 5), // "value"
QT_MOC_LITERAL(17, 195, 20), // "RequestVariableValue"
QT_MOC_LITERAL(18, 216, 10), // "QIODevice*"
QT_MOC_LITERAL(19, 227, 6), // "sender"
QT_MOC_LITERAL(20, 234, 27), // "ReceiveRequestsFromExternal"
QT_MOC_LITERAL(21, 262, 7), // "request"
QT_MOC_LITERAL(22, 270, 8), // "ReadData"
QT_MOC_LITERAL(23, 279, 14), // "FindingTimeOut"
QT_MOC_LITERAL(24, 294, 30), // "ReceiveNewConnectionFromServer"
QT_MOC_LITERAL(25, 325, 11), // "QTcpSocket*"
QT_MOC_LITERAL(26, 337, 6) // "socket"

    },
    "ConnectionManager\0FinishReadLine\0\0msg\0"
    "ExternalMCUTransmitText\0text\0"
    "DeltaResponeReady\0DeltaResponeGcodeDone\0"
    "InHomePosition\0x\0y\0z\0w\0ReceiveConvenyorPosition\0"
    "ReceiveVariableChangeCommand\0name\0"
    "value\0RequestVariableValue\0QIODevice*\0"
    "sender\0ReceiveRequestsFromExternal\0"
    "request\0ReadData\0FindingTimeOut\0"
    "ReceiveNewConnectionFromServer\0"
    "QTcpSocket*\0socket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       6,    0,   80,    2, 0x06 /* Public */,
       7,    0,   81,    2, 0x06 /* Public */,
       8,    4,   82,    2, 0x06 /* Public */,
      13,    2,   91,    2, 0x06 /* Public */,
      14,    2,   96,    2, 0x06 /* Public */,
      17,    2,  101,    2, 0x06 /* Public */,
      20,    1,  106,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    0,  109,    2, 0x0a /* Public */,
      23,    0,  110,    2, 0x0a /* Public */,
      24,    1,  111,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    9,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::Float,   15,   16,
    QMetaType::Void, 0x80000000 | 18, QMetaType::QString,   19,   15,
    QMetaType::Void, QMetaType::QString,   21,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,

       0        // eod
};

void ConnectionManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConnectionManager *_t = static_cast<ConnectionManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->FinishReadLine((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ExternalMCUTransmitText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->DeltaResponeReady(); break;
        case 3: _t->DeltaResponeGcodeDone(); break;
        case 4: _t->InHomePosition((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 5: _t->ReceiveConvenyorPosition((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->ReceiveVariableChangeCommand((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 7: _t->RequestVariableValue((*reinterpret_cast< QIODevice*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->ReceiveRequestsFromExternal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->ReadData(); break;
        case 10: _t->FindingTimeOut(); break;
        case 11: _t->ReceiveNewConnectionFromServer((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QIODevice* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ConnectionManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConnectionManager::FinishReadLine)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ConnectionManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConnectionManager::ExternalMCUTransmitText)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ConnectionManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConnectionManager::DeltaResponeReady)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ConnectionManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConnectionManager::DeltaResponeGcodeDone)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ConnectionManager::*_t)(float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConnectionManager::InHomePosition)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ConnectionManager::*_t)(float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConnectionManager::ReceiveConvenyorPosition)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ConnectionManager::*_t)(QString , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConnectionManager::ReceiveVariableChangeCommand)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ConnectionManager::*_t)(QIODevice * , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConnectionManager::RequestVariableValue)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (ConnectionManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConnectionManager::ReceiveRequestsFromExternal)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject ConnectionManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ConnectionManager.data,
      qt_meta_data_ConnectionManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConnectionManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionManager.stringdata0))
        return static_cast<void*>(const_cast< ConnectionManager*>(this));
    return QObject::qt_metacast(_clname);
}

int ConnectionManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ConnectionManager::FinishReadLine(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConnectionManager::ExternalMCUTransmitText(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConnectionManager::DeltaResponeReady()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ConnectionManager::DeltaResponeGcodeDone()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void ConnectionManager::InHomePosition(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ConnectionManager::ReceiveConvenyorPosition(float _t1, float _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ConnectionManager::ReceiveVariableChangeCommand(QString _t1, float _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ConnectionManager::RequestVariableValue(QIODevice * _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ConnectionManager::ReceiveRequestsFromExternal(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
