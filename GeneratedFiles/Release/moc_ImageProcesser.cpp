/****************************************************************************
** Meta object code from reading C++ file 'ImageProcesser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ImageProcesser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageProcesser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageProcesser_t {
    QByteArrayData data[15];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageProcesser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageProcesser_t qt_meta_stringdata_ImageProcesser = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ImageProcesser"
QT_MOC_LITERAL(1, 15, 13), // "LoadTestImage"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "LoadCamera"
QT_MOC_LITERAL(4, 41, 18), // "UpdateCameraScreen"
QT_MOC_LITERAL(5, 60, 18), // "OpenParameterPanel"
QT_MOC_LITERAL(6, 79, 6), // "SetHSV"
QT_MOC_LITERAL(7, 86, 4), // "minH"
QT_MOC_LITERAL(8, 91, 4), // "maxH"
QT_MOC_LITERAL(9, 96, 4), // "minS"
QT_MOC_LITERAL(10, 101, 4), // "maxS"
QT_MOC_LITERAL(11, 106, 4), // "minV"
QT_MOC_LITERAL(12, 111, 4), // "maxV"
QT_MOC_LITERAL(13, 116, 12), // "SetThreshold"
QT_MOC_LITERAL(14, 129, 5) // "value"

    },
    "ImageProcesser\0LoadTestImage\0\0LoadCamera\0"
    "UpdateCameraScreen\0OpenParameterPanel\0"
    "SetHSV\0minH\0maxH\0minS\0maxS\0minV\0maxV\0"
    "SetThreshold\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageProcesser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    6,   48,    2, 0x0a /* Public */,
      13,    1,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,    9,   10,   11,   12,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void ImageProcesser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageProcesser *_t = static_cast<ImageProcesser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LoadTestImage(); break;
        case 1: _t->LoadCamera(); break;
        case 2: _t->UpdateCameraScreen(); break;
        case 3: _t->OpenParameterPanel(); break;
        case 4: _t->SetHSV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 5: _t->SetThreshold((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ImageProcesser::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageProcesser.data,
      qt_meta_data_ImageProcesser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageProcesser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageProcesser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageProcesser.stringdata0))
        return static_cast<void*>(const_cast< ImageProcesser*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageProcesser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
