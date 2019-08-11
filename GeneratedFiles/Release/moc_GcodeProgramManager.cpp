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
#include <QtCore/QList>
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
    QByteArrayData data[24];
    char stringdata0[337];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GcodeProgramManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GcodeProgramManager_t qt_meta_stringdata_GcodeProgramManager = {
    {
QT_MOC_LITERAL(0, 0, 19), // "GcodeProgramManager"
QT_MOC_LITERAL(1, 20, 19), // "OutOfObjectVariable"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 18), // "JustUpdateVariable"
QT_MOC_LITERAL(4, 60, 20), // "QList<GcodeVariable>"
QT_MOC_LITERAL(5, 81, 14), // "gcodeVariables"
QT_MOC_LITERAL(6, 96, 17), // "MoveToNewPosition"
QT_MOC_LITERAL(7, 114, 1), // "x"
QT_MOC_LITERAL(8, 116, 1), // "y"
QT_MOC_LITERAL(9, 118, 1), // "z"
QT_MOC_LITERAL(10, 120, 1), // "w"
QT_MOC_LITERAL(11, 122, 22), // "ChangeSelectingProgram"
QT_MOC_LITERAL(12, 145, 13), // "GcodeProgram*"
QT_MOC_LITERAL(13, 159, 3), // "ptr"
QT_MOC_LITERAL(14, 163, 17), // "SaveGcodeIntoFile"
QT_MOC_LITERAL(15, 181, 13), // "DeleteProgram"
QT_MOC_LITERAL(16, 195, 21), // "EraserAllProgramItems"
QT_MOC_LITERAL(17, 217, 16), // "SortProgramFiles"
QT_MOC_LITERAL(18, 234, 23), // "RefreshGcodeProgramList"
QT_MOC_LITERAL(19, 258, 17), // "TransmitNextGcode"
QT_MOC_LITERAL(20, 276, 20), // "UpdateSystemVariable"
QT_MOC_LITERAL(21, 297, 4), // "name"
QT_MOC_LITERAL(22, 302, 5), // "value"
QT_MOC_LITERAL(23, 308, 28) // "SetStartingGcodeEditorCursor"

    },
    "GcodeProgramManager\0OutOfObjectVariable\0"
    "\0JustUpdateVariable\0QList<GcodeVariable>\0"
    "gcodeVariables\0MoveToNewPosition\0x\0y\0"
    "z\0w\0ChangeSelectingProgram\0GcodeProgram*\0"
    "ptr\0SaveGcodeIntoFile\0DeleteProgram\0"
    "EraserAllProgramItems\0SortProgramFiles\0"
    "RefreshGcodeProgramList\0TransmitNextGcode\0"
    "UpdateSystemVariable\0name\0value\0"
    "SetStartingGcodeEditorCursor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GcodeProgramManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       6,    4,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   87,    2, 0x0a /* Public */,
      14,    0,   90,    2, 0x0a /* Public */,
      15,    1,   91,    2, 0x0a /* Public */,
      16,    0,   94,    2, 0x0a /* Public */,
      17,    0,   95,    2, 0x0a /* Public */,
      18,    0,   96,    2, 0x0a /* Public */,
      19,    0,   97,    2, 0x0a /* Public */,
      20,    2,   98,    2, 0x0a /* Public */,
      23,    1,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    7,    8,    9,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Float,   21,   22,
    QMetaType::Void, QMetaType::QString,   22,

       0        // eod
};

void GcodeProgramManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GcodeProgramManager *_t = static_cast<GcodeProgramManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OutOfObjectVariable(); break;
        case 1: _t->JustUpdateVariable((*reinterpret_cast< QList<GcodeVariable>(*)>(_a[1]))); break;
        case 2: _t->MoveToNewPosition((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 3: _t->ChangeSelectingProgram((*reinterpret_cast< GcodeProgram*(*)>(_a[1]))); break;
        case 4: _t->SaveGcodeIntoFile(); break;
        case 5: _t->DeleteProgram((*reinterpret_cast< GcodeProgram*(*)>(_a[1]))); break;
        case 6: _t->EraserAllProgramItems(); break;
        case 7: _t->SortProgramFiles(); break;
        case 8: _t->RefreshGcodeProgramList(); break;
        case 9: _t->TransmitNextGcode(); break;
        case 10: _t->UpdateSystemVariable((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 11: _t->SetStartingGcodeEditorCursor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GcodeProgram* >(); break;
            }
            break;
        case 5:
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
            typedef void (GcodeProgramManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgramManager::OutOfObjectVariable)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GcodeProgramManager::*_t)(QList<GcodeVariable> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgramManager::JustUpdateVariable)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GcodeProgramManager::*_t)(float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgramManager::MoveToNewPosition)) {
                *result = 2;
                return;
            }
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
void GcodeProgramManager::OutOfObjectVariable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void GcodeProgramManager::JustUpdateVariable(QList<GcodeVariable> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GcodeProgramManager::MoveToNewPosition(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
