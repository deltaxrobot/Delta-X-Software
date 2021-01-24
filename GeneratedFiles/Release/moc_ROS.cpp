/****************************************************************************
** Meta object code from reading C++ file 'ROS.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ROS.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ROS.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ROS_t {
    QByteArrayData data[19];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ROS_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ROS_t qt_meta_stringdata_ROS = {
    {
QT_MOC_LITERAL(0, 0, 3), // "ROS"
QT_MOC_LITERAL(1, 4, 3), // "Run"
QT_MOC_LITERAL(2, 8, 0), // ""
QT_MOC_LITERAL(3, 9, 20), // "SetConnectionManager"
QT_MOC_LITERAL(4, 30, 21), // "TCPConnectionManager*"
QT_MOC_LITERAL(5, 52, 12), // "connectionMg"
QT_MOC_LITERAL(6, 65, 9), // "ResetView"
QT_MOC_LITERAL(7, 75, 10), // "ProcessROS"
QT_MOC_LITERAL(8, 86, 10), // "GetDisplay"
QT_MOC_LITERAL(9, 97, 7), // "QFrame*"
QT_MOC_LITERAL(10, 105, 5), // "Foces"
QT_MOC_LITERAL(11, 111, 16), // "GetDisplayLayout"
QT_MOC_LITERAL(12, 128, 8), // "QLayout*"
QT_MOC_LITERAL(13, 137, 9), // "IsRunning"
QT_MOC_LITERAL(14, 147, 5), // "Close"
QT_MOC_LITERAL(15, 153, 12), // "G01_Relative"
QT_MOC_LITERAL(16, 166, 1), // "x"
QT_MOC_LITERAL(17, 168, 1), // "y"
QT_MOC_LITERAL(18, 170, 1) // "z"

    },
    "ROS\0Run\0\0SetConnectionManager\0"
    "TCPConnectionManager*\0connectionMg\0"
    "ResetView\0ProcessROS\0GetDisplay\0QFrame*\0"
    "Foces\0GetDisplayLayout\0QLayout*\0"
    "IsRunning\0Close\0G01_Relative\0x\0y\0z"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ROS[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    1,   65,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
      10,    0,   71,    2, 0x0a /* Public */,
      11,    0,   72,    2, 0x0a /* Public */,
      13,    0,   73,    2, 0x0a /* Public */,
      14,    0,   74,    2, 0x0a /* Public */,
      15,    3,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 9,
    QMetaType::Void,
    0x80000000 | 12,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float,   16,   17,   18,

       0        // eod
};

void ROS::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ROS *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Run(); break;
        case 1: _t->SetConnectionManager((*reinterpret_cast< TCPConnectionManager*(*)>(_a[1]))); break;
        case 2: _t->ResetView(); break;
        case 3: _t->ProcessROS(); break;
        case 4: { QFrame* _r = _t->GetDisplay();
            if (_a[0]) *reinterpret_cast< QFrame**>(_a[0]) = std::move(_r); }  break;
        case 5: _t->Foces(); break;
        case 6: { QLayout* _r = _t->GetDisplayLayout();
            if (_a[0]) *reinterpret_cast< QLayout**>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->IsRunning();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->Close(); break;
        case 9: _t->G01_Relative((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TCPConnectionManager* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ROS::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ROS.data,
    qt_meta_data_ROS,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ROS::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ROS::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ROS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ROS::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
