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
    QByteArrayData data[8];
    char stringdata0[51];
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
QT_MOC_LITERAL(6, 29, 12), // "FinishMoving"
QT_MOC_LITERAL(7, 42, 8) // "ChangeXY"

    },
    "DeltaVisualizer\0Moved\0\0x\0y\0z\0FinishMoving\0"
    "ChangeXY"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeltaVisualizer[] = {

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
       1,    3,   29,    2, 0x06 /* Public */,
       6,    0,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

       0        // eod
};

void DeltaVisualizer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DeltaVisualizer *_t = static_cast<DeltaVisualizer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Moved((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 1: _t->FinishMoving(); break;
        case 2: _t->ChangeXY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DeltaVisualizer::*_t)(float , float , float );
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
void DeltaVisualizer::Moved(float _t1, float _t2, float _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DeltaVisualizer::FinishMoving()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
