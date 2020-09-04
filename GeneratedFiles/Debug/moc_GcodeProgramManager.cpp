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
    QByteArrayData data[35];
    char stringdata0[470];
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
QT_MOC_LITERAL(11, 122, 1), // "f"
QT_MOC_LITERAL(12, 124, 1), // "a"
QT_MOC_LITERAL(13, 126, 19), // "FinishExecuteGcodes"
QT_MOC_LITERAL(14, 146, 16), // "DeleteAllObjects"
QT_MOC_LITERAL(15, 163, 13), // "DeleteObject1"
QT_MOC_LITERAL(16, 177, 11), // "PauseCamera"
QT_MOC_LITERAL(17, 189, 13), // "CaptureCamera"
QT_MOC_LITERAL(18, 203, 12), // "ResumeCamera"
QT_MOC_LITERAL(19, 216, 22), // "ChangeSelectingProgram"
QT_MOC_LITERAL(20, 239, 13), // "GcodeProgram*"
QT_MOC_LITERAL(21, 253, 3), // "ptr"
QT_MOC_LITERAL(22, 257, 17), // "SaveGcodeIntoFile"
QT_MOC_LITERAL(23, 275, 13), // "DeleteProgram"
QT_MOC_LITERAL(24, 289, 21), // "EraserAllProgramItems"
QT_MOC_LITERAL(25, 311, 16), // "SortProgramFiles"
QT_MOC_LITERAL(26, 328, 23), // "RefreshGcodeProgramList"
QT_MOC_LITERAL(27, 352, 17), // "TransmitNextGcode"
QT_MOC_LITERAL(28, 370, 20), // "UpdateSystemVariable"
QT_MOC_LITERAL(29, 391, 4), // "name"
QT_MOC_LITERAL(30, 396, 5), // "value"
QT_MOC_LITERAL(31, 402, 20), // "RespondVariableValue"
QT_MOC_LITERAL(32, 423, 10), // "QIODevice*"
QT_MOC_LITERAL(33, 434, 6), // "sender"
QT_MOC_LITERAL(34, 441, 28) // "SetStartingGcodeEditorCursor"

    },
    "GcodeProgramManager\0OutOfObjectVariable\0"
    "\0JustUpdateVariable\0QList<GcodeVariable>\0"
    "gcodeVariables\0MoveToNewPosition\0x\0y\0"
    "z\0w\0f\0a\0FinishExecuteGcodes\0"
    "DeleteAllObjects\0DeleteObject1\0"
    "PauseCamera\0CaptureCamera\0ResumeCamera\0"
    "ChangeSelectingProgram\0GcodeProgram*\0"
    "ptr\0SaveGcodeIntoFile\0DeleteProgram\0"
    "EraserAllProgramItems\0SortProgramFiles\0"
    "RefreshGcodeProgramList\0TransmitNextGcode\0"
    "UpdateSystemVariable\0name\0value\0"
    "RespondVariableValue\0QIODevice*\0sender\0"
    "SetStartingGcodeEditorCursor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GcodeProgramManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  109,    2, 0x06 /* Public */,
       3,    1,  110,    2, 0x06 /* Public */,
       6,    6,  113,    2, 0x06 /* Public */,
      13,    0,  126,    2, 0x06 /* Public */,
      14,    0,  127,    2, 0x06 /* Public */,
      15,    0,  128,    2, 0x06 /* Public */,
      16,    0,  129,    2, 0x06 /* Public */,
      17,    0,  130,    2, 0x06 /* Public */,
      18,    0,  131,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    1,  132,    2, 0x0a /* Public */,
      22,    0,  135,    2, 0x0a /* Public */,
      23,    1,  136,    2, 0x0a /* Public */,
      24,    0,  139,    2, 0x0a /* Public */,
      25,    0,  140,    2, 0x0a /* Public */,
      26,    0,  141,    2, 0x0a /* Public */,
      27,    0,  142,    2, 0x0a /* Public */,
      28,    2,  143,    2, 0x0a /* Public */,
      31,    2,  148,    2, 0x0a /* Public */,
      34,    1,  153,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    7,    8,    9,   10,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Float,   29,   30,
    QMetaType::Void, 0x80000000 | 32, QMetaType::QString,   33,   29,
    QMetaType::Void, QMetaType::QString,   30,

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
        case 2: _t->MoveToNewPosition((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6]))); break;
        case 3: _t->FinishExecuteGcodes(); break;
        case 4: _t->DeleteAllObjects(); break;
        case 5: _t->DeleteObject1(); break;
        case 6: _t->PauseCamera(); break;
        case 7: _t->CaptureCamera(); break;
        case 8: _t->ResumeCamera(); break;
        case 9: _t->ChangeSelectingProgram((*reinterpret_cast< GcodeProgram*(*)>(_a[1]))); break;
        case 10: _t->SaveGcodeIntoFile(); break;
        case 11: _t->DeleteProgram((*reinterpret_cast< GcodeProgram*(*)>(_a[1]))); break;
        case 12: _t->EraserAllProgramItems(); break;
        case 13: _t->SortProgramFiles(); break;
        case 14: _t->RefreshGcodeProgramList(); break;
        case 15: _t->TransmitNextGcode(); break;
        case 16: _t->UpdateSystemVariable((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 17: _t->RespondVariableValue((*reinterpret_cast< QIODevice*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: _t->SetStartingGcodeEditorCursor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GcodeProgram* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< GcodeProgram* >(); break;
            }
            break;
        case 17:
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
            typedef void (GcodeProgramManager::*_t)(float , float , float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgramManager::MoveToNewPosition)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GcodeProgramManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgramManager::FinishExecuteGcodes)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (GcodeProgramManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgramManager::DeleteAllObjects)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (GcodeProgramManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgramManager::DeleteObject1)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (GcodeProgramManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgramManager::PauseCamera)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (GcodeProgramManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgramManager::CaptureCamera)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (GcodeProgramManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GcodeProgramManager::ResumeCamera)) {
                *result = 8;
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
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
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
void GcodeProgramManager::MoveToNewPosition(float _t1, float _t2, float _t3, float _t4, float _t5, float _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GcodeProgramManager::FinishExecuteGcodes()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void GcodeProgramManager::DeleteAllObjects()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void GcodeProgramManager::DeleteObject1()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void GcodeProgramManager::PauseCamera()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void GcodeProgramManager::CaptureCamera()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void GcodeProgramManager::ResumeCamera()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
