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
    QByteArrayData data[24];
    char stringdata0[269];
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
QT_MOC_LITERAL(12, 73, 21), // "FinishSelectCalibLine"
QT_MOC_LITERAL(13, 95, 18), // "FinishMeasureSpace"
QT_MOC_LITERAL(14, 114, 8), // "distance"
QT_MOC_LITERAL(15, 123, 22), // "FinishSelectCalibPoint"
QT_MOC_LITERAL(16, 146, 10), // "rectObject"
QT_MOC_LITERAL(17, 157, 10), // "lineObject"
QT_MOC_LITERAL(18, 168, 12), // "circleObject"
QT_MOC_LITERAL(19, 181, 19), // "selectProcessRegion"
QT_MOC_LITERAL(20, 201, 25), // "ChangeCalibLineRealLength"
QT_MOC_LITERAL(21, 227, 5), // "value"
QT_MOC_LITERAL(22, 233, 17), // "ChangeXCalibPoint"
QT_MOC_LITERAL(23, 251, 17) // "ChangeYCalibPoint"

    },
    "CameraWidget\0FinishDrawObject\0\0x\0y\0h\0"
    "w\0FinishSelectProcessRegion\0a\0b\0c\0d\0"
    "FinishSelectCalibLine\0FinishMeasureSpace\0"
    "distance\0FinishSelectCalibPoint\0"
    "rectObject\0lineObject\0circleObject\0"
    "selectProcessRegion\0ChangeCalibLineRealLength\0"
    "value\0ChangeXCalibPoint\0ChangeYCalibPoint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   74,    2, 0x06 /* Public */,
       7,    4,   83,    2, 0x06 /* Public */,
      12,    2,   92,    2, 0x06 /* Public */,
      13,    1,   97,    2, 0x06 /* Public */,
      15,    2,  100,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,  105,    2, 0x0a /* Public */,
      17,    0,  106,    2, 0x0a /* Public */,
      18,    0,  107,    2, 0x0a /* Public */,
      19,    0,  108,    2, 0x0a /* Public */,
      20,    1,  109,    2, 0x0a /* Public */,
      22,    1,  112,    2, 0x0a /* Public */,
      23,    1,  115,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QPoint,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint,    8,    9,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   21,

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
        case 2: _t->FinishSelectCalibLine((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 3: _t->FinishMeasureSpace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->FinishSelectCalibPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->rectObject(); break;
        case 6: _t->lineObject(); break;
        case 7: _t->circleObject(); break;
        case 8: _t->selectProcessRegion(); break;
        case 9: _t->ChangeCalibLineRealLength((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->ChangeXCalibPoint((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->ChangeYCalibPoint((*reinterpret_cast< QString(*)>(_a[1]))); break;
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
            typedef void (CameraWidget::*_t)(QPoint , QPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishSelectCalibLine)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CameraWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishMeasureSpace)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CameraWidget::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishSelectCalibPoint)) {
                *result = 4;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
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
void CameraWidget::FinishSelectCalibLine(QPoint _t1, QPoint _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CameraWidget::FinishMeasureSpace(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CameraWidget::FinishSelectCalibPoint(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
