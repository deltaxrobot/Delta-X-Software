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
    QByteArrayData data[30];
    char stringdata0[354];
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
QT_MOC_LITERAL(7, 39, 29), // "FinishSelectPerspectivePoints"
QT_MOC_LITERAL(8, 69, 1), // "a"
QT_MOC_LITERAL(9, 71, 1), // "b"
QT_MOC_LITERAL(10, 73, 1), // "c"
QT_MOC_LITERAL(11, 75, 1), // "d"
QT_MOC_LITERAL(12, 77, 28), // "FinishSelectProcessRectangle"
QT_MOC_LITERAL(13, 106, 4), // "rect"
QT_MOC_LITERAL(14, 111, 21), // "FinishSelectCalibLine"
QT_MOC_LITERAL(15, 133, 18), // "FinishMeasureSpace"
QT_MOC_LITERAL(16, 152, 8), // "distance"
QT_MOC_LITERAL(17, 161, 22), // "FinishSelectCalibPoint"
QT_MOC_LITERAL(18, 184, 11), // "SizeChanged"
QT_MOC_LITERAL(19, 196, 10), // "rectObject"
QT_MOC_LITERAL(20, 207, 10), // "lineObject"
QT_MOC_LITERAL(21, 218, 12), // "circleObject"
QT_MOC_LITERAL(22, 231, 26), // "selectPerspectiveRectangle"
QT_MOC_LITERAL(23, 258, 22), // "selectProcessRectangle"
QT_MOC_LITERAL(24, 281, 6), // "noTool"
QT_MOC_LITERAL(25, 288, 11), // "SaveSetting"
QT_MOC_LITERAL(26, 300, 11), // "LoadSetting"
QT_MOC_LITERAL(27, 312, 17), // "ChangeXCalibPoint"
QT_MOC_LITERAL(28, 330, 5), // "value"
QT_MOC_LITERAL(29, 336, 17) // "ChangeYCalibPoint"

    },
    "CameraWidget\0FinishDrawObject\0\0x\0y\0h\0"
    "w\0FinishSelectPerspectivePoints\0a\0b\0"
    "c\0d\0FinishSelectProcessRectangle\0rect\0"
    "FinishSelectCalibLine\0FinishMeasureSpace\0"
    "distance\0FinishSelectCalibPoint\0"
    "SizeChanged\0rectObject\0lineObject\0"
    "circleObject\0selectPerspectiveRectangle\0"
    "selectProcessRectangle\0noTool\0SaveSetting\0"
    "LoadSetting\0ChangeXCalibPoint\0value\0"
    "ChangeYCalibPoint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   99,    2, 0x06 /* Public */,
       7,    4,  108,    2, 0x06 /* Public */,
      12,    1,  117,    2, 0x06 /* Public */,
      14,    2,  120,    2, 0x06 /* Public */,
      15,    1,  125,    2, 0x06 /* Public */,
      17,    2,  128,    2, 0x06 /* Public */,
      18,    0,  133,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    0,  134,    2, 0x0a /* Public */,
      20,    0,  135,    2, 0x0a /* Public */,
      21,    0,  136,    2, 0x0a /* Public */,
      22,    0,  137,    2, 0x0a /* Public */,
      23,    0,  138,    2, 0x0a /* Public */,
      24,    0,  139,    2, 0x0a /* Public */,
      25,    0,  140,    2, 0x0a /* Public */,
      26,    0,  141,    2, 0x0a /* Public */,
      27,    1,  142,    2, 0x0a /* Public */,
      29,    1,  145,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QPoint,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::QRect,   13,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint,    8,    9,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QString,   28,

       0        // eod
};

void CameraWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraWidget *_t = static_cast<CameraWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->FinishDrawObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->FinishSelectPerspectivePoints((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2])),(*reinterpret_cast< QPoint(*)>(_a[3])),(*reinterpret_cast< QPoint(*)>(_a[4]))); break;
        case 2: _t->FinishSelectProcessRectangle((*reinterpret_cast< QRect(*)>(_a[1]))); break;
        case 3: _t->FinishSelectCalibLine((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 4: _t->FinishMeasureSpace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->FinishSelectCalibPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->SizeChanged(); break;
        case 7: _t->rectObject(); break;
        case 8: _t->lineObject(); break;
        case 9: _t->circleObject(); break;
        case 10: _t->selectPerspectiveRectangle(); break;
        case 11: _t->selectProcessRectangle(); break;
        case 12: _t->noTool(); break;
        case 13: _t->SaveSetting(); break;
        case 14: _t->LoadSetting(); break;
        case 15: _t->ChangeXCalibPoint((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->ChangeYCalibPoint((*reinterpret_cast< QString(*)>(_a[1]))); break;
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
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishSelectPerspectivePoints)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CameraWidget::*_t)(QRect );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishSelectProcessRectangle)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CameraWidget::*_t)(QPoint , QPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishSelectCalibLine)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CameraWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishMeasureSpace)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (CameraWidget::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::FinishSelectCalibPoint)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (CameraWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CameraWidget::SizeChanged)) {
                *result = 6;
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
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
void CameraWidget::FinishSelectPerspectivePoints(QPoint _t1, QPoint _t2, QPoint _t3, QPoint _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CameraWidget::FinishSelectProcessRectangle(QRect _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CameraWidget::FinishSelectCalibLine(QPoint _t1, QPoint _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CameraWidget::FinishMeasureSpace(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CameraWidget::FinishSelectCalibPoint(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CameraWidget::SizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
