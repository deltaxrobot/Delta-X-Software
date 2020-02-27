/****************************************************************************
** Meta object code from reading C++ file 'DeltaVisualizer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DeltaVisualizer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DeltaVisualizer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeltaVisualizer_t {
    QByteArrayData data[19];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeltaVisualizer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeltaVisualizer_t qt_meta_stringdata_DeltaVisualizer = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DeltaVisualizer"
QT_MOC_LITERAL(1, 16, 5), // "Moved"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 1), // "x"
QT_MOC_LITERAL(4, 25, 1), // "y"
QT_MOC_LITERAL(5, 27, 1), // "z"
QT_MOC_LITERAL(6, 29, 1), // "w"
QT_MOC_LITERAL(7, 31, 12), // "FinishMoving"
QT_MOC_LITERAL(8, 44, 8), // "up_arrow"
QT_MOC_LITERAL(9, 53, 10), // "down_arrow"
QT_MOC_LITERAL(10, 64, 10), // "left_arrow"
QT_MOC_LITERAL(11, 75, 11), // "right_arrow"
QT_MOC_LITERAL(12, 87, 8), // "ChangeXY"
QT_MOC_LITERAL(13, 96, 6), // "MoveUp"
QT_MOC_LITERAL(14, 103, 8), // "MoveDown"
QT_MOC_LITERAL(15, 112, 11), // "MoveForward"
QT_MOC_LITERAL(16, 124, 12), // "MoveBackward"
QT_MOC_LITERAL(17, 137, 8), // "MoveLeft"
QT_MOC_LITERAL(18, 146, 9) // "MoveRight"

    },
    "DeltaVisualizer\0Moved\0\0x\0y\0z\0w\0"
    "FinishMoving\0up_arrow\0down_arrow\0"
    "left_arrow\0right_arrow\0ChangeXY\0MoveUp\0"
    "MoveDown\0MoveForward\0MoveBackward\0"
    "MoveLeft\0MoveRight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeltaVisualizer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   79,    2, 0x06 /* Public */,
       7,    0,   88,    2, 0x06 /* Public */,
       8,    0,   89,    2, 0x06 /* Public */,
       9,    0,   90,    2, 0x06 /* Public */,
      10,    0,   91,    2, 0x06 /* Public */,
      11,    0,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,   93,    2, 0x0a /* Public */,
      13,    0,   98,    2, 0x0a /* Public */,
      14,    0,   99,    2, 0x0a /* Public */,
      15,    0,  100,    2, 0x0a /* Public */,
      16,    0,  101,    2, 0x0a /* Public */,
      17,    0,  102,    2, 0x0a /* Public */,
      18,    0,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DeltaVisualizer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DeltaVisualizer *_t = static_cast<DeltaVisualizer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Moved((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 1: _t->FinishMoving(); break;
        case 2: _t->up_arrow(); break;
        case 3: _t->down_arrow(); break;
        case 4: _t->left_arrow(); break;
        case 5: _t->right_arrow(); break;
        case 6: _t->ChangeXY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->MoveUp(); break;
        case 8: _t->MoveDown(); break;
        case 9: _t->MoveForward(); break;
        case 10: _t->MoveBackward(); break;
        case 11: _t->MoveLeft(); break;
        case 12: _t->MoveRight(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DeltaVisualizer::*_t)(float , float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeltaVisualizer::Moved)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DeltaVisualizer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeltaVisualizer::FinishMoving)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DeltaVisualizer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeltaVisualizer::up_arrow)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DeltaVisualizer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeltaVisualizer::down_arrow)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (DeltaVisualizer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeltaVisualizer::left_arrow)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (DeltaVisualizer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DeltaVisualizer::right_arrow)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject DeltaVisualizer::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_DeltaVisualizer.data,
      qt_meta_data_DeltaVisualizer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DeltaVisualizer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeltaVisualizer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DeltaVisualizer.stringdata0))
        return static_cast<void*>(const_cast< DeltaVisualizer*>(this));
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(const_cast< DeltaVisualizer*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int DeltaVisualizer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void DeltaVisualizer::Moved(float _t1, float _t2, float _t3, float _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeltaVisualizer::FinishMoving()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void DeltaVisualizer::up_arrow()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void DeltaVisualizer::down_arrow()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void DeltaVisualizer::left_arrow()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void DeltaVisualizer::right_arrow()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
