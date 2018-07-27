/****************************************************************************
** Meta object code from reading C++ file 'GcodeProgramManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GcodeProgramManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GcodeProgramManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GcodeProgramManager_t {
    QByteArrayData data[7];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GcodeProgramManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GcodeProgramManager_t qt_meta_stringdata_GcodeProgramManager = {
    {
QT_MOC_LITERAL(0, 0, 19), // "GcodeProgramManager"
QT_MOC_LITERAL(1, 20, 22), // "ChangeSelectingProgram"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 13), // "GcodeProgram*"
QT_MOC_LITERAL(4, 58, 3), // "ptr"
QT_MOC_LITERAL(5, 62, 17), // "SaveGcodeIntoFile"
QT_MOC_LITERAL(6, 80, 13) // "DeleteProgram"

    },
    "GcodeProgramManager\0ChangeSelectingProgram\0"
    "\0GcodeProgram*\0ptr\0SaveGcodeIntoFile\0"
    "DeleteProgram"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GcodeProgramManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       5,    0,   32,    2, 0x0a /* Public */,
       6,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void GcodeProgramManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GcodeProgramManager *_t = static_cast<GcodeProgramManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ChangeSelectingProgram((*reinterpret_cast< GcodeProgram*(*)>(_a[1]))); break;
        case 1: _t->SaveGcodeIntoFile(); break;
        case 2: _t->DeleteProgram((*reinterpret_cast< GcodeProgram*(*)>(_a[1]))); break;
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
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GcodeProgram* >(); break;
            }
            break;
        }
    }
}

const QMetaObject GcodeProgramManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GcodeProgramManager.data,
      qt_meta_data_GcodeProgramManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GcodeProgramManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GcodeProgramManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GcodeProgramManager.stringdata0))
        return static_cast<void*>(const_cast< GcodeProgramManager*>(this));
    return QObject::qt_metacast(_clname);
}

int GcodeProgramManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
