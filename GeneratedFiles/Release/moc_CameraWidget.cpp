/****************************************************************************
** Meta object code from reading C++ file 'CameraWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CameraWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CameraWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CameraWidget_t {
    QByteArrayData data[19];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraWidget_t qt_meta_stringdata_CameraWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CameraWidget"
QT_MOC_LITERAL(1, 13, 16), // "FinishDrawObject"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 1), // "x"
QT_MOC_LITERAL(4, 33, 1), // "y"
QT_MOC_LITERAL(5, 35, 1), // "h"
QT_MOC_LITERAL(6, 37, 1), // "w"
QT_MOC_LITERAL(7, 39, 25), // "FinishSelectProcessRegion"
QT_MOC_LITERAL(8, 65, 1), // "a"
QT_MOC_LITERAL(9, 67, 1), // "b"
QT_MOC_LITERAL(10, 69, 1), // "c"
QT_MOC_LITERAL(11, 71, 1), // "d"
QT_MOC_LITERAL(12, 73, 18), // "FinishMeasureSpace"
QT_MOC_LITERAL(13, 92, 8), // "distance"
QT_MOC_LITERAL(14, 101, 22), // "FinishSelectCalibPoint"
QT_MOC_LITERAL(15, 124, 10), // "rectObject"
QT_MOC_LITERAL(16, 135, 10), // "lineObject"
QT_MOC_LITERAL(17, 146, 12), // "circleObject"
QT_MOC_LITERAL(18, 159, 19) // "selectProcessRegion"

    },
    "CameraWidget\0FinishDrawObject\0\0x\0y\0h\0"
    "w\0FinishSelectProcessRegion\0a\0b\0c\0d\0"
    "FinishMeasureSpace\0distance\0"
    "FinishSelectCalibPoint\0rectObject\0"
    "lineObject\0circleObject\0selectProcessRegion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   54,    2, 0x06 /* Public */,
       7,    4,   63,    2, 0x06 /* Public */,
      12,    1,   72,    2, 0x06 /* Public */,
      14,    2,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,   80,    2, 0x0a /* Public */,
      16,    0,   81,    2, 0x0a /* Public */,
      17,    0,   82,    2, 0x0a /* Public */,
      18,    0,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QPoint,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CameraWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraWidget *_t = static_cast<CameraWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->FinishDrawObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->FinishSelectProcessRegion((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2])),(*reinterpret_cast< QPoint(*)>(_a[3])),(*reinterpret_cast< QPoint(*)>(_a[4]))); break;
        case 2: _t->FinishMeasureSpace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->FinishSelectCalibPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->rectObject(); break;
        case 5: _t->lineObject(); break;
        case 6: _t->circleObject(); break;
        case 7: _t->selectProcessRegion(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CameraWidget::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishDrawObject)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CameraWidget::*_t)(QPoint , QPoint , QPoint , QPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishSelectProcessRegion)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CameraWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishMeasureSpace)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CameraWidget::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishSelectCalibPoint)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject CameraWidget::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_CameraWidget.data,
      qt_meta_data_CameraWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CameraWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CameraWidget.stringdata0))
        return static_cast<void*>(const_cast< CameraWidget*>(this));
    return QLabel::qt_metacast(_clname);
}

int CameraWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CameraWidget::FinishDrawObject(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CameraWidget::FinishSelectProcessRegion(QPoint _t1, QPoint _t2, QPoint _t3, QPoint _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CameraWidget::FinishMeasureSpace(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CameraWidget::FinishSelectCalibPoint(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
