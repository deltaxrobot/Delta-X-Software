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
    QByteArrayData data[36];
    char stringdata0[367];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageProcesser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageProcesser_t qt_meta_stringdata_ImageProcesser = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ImageProcesser"
QT_MOC_LITERAL(1, 15, 18), // "ObjectValueChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 28), // "std::vector<cv::RotatedRect>"
QT_MOC_LITERAL(4, 64, 15), // "ObjectContainer"
QT_MOC_LITERAL(5, 80, 13), // "LoadTestImage"
QT_MOC_LITERAL(6, 94, 10), // "LoadCamera"
QT_MOC_LITERAL(7, 105, 24), // "CaptureAnImageFromCamera"
QT_MOC_LITERAL(8, 130, 18), // "UpdateCameraScreen"
QT_MOC_LITERAL(9, 149, 7), // "SaveFPS"
QT_MOC_LITERAL(10, 157, 18), // "OpenParameterPanel"
QT_MOC_LITERAL(11, 176, 6), // "SetHSV"
QT_MOC_LITERAL(12, 183, 4), // "minH"
QT_MOC_LITERAL(13, 188, 4), // "maxH"
QT_MOC_LITERAL(14, 193, 4), // "minS"
QT_MOC_LITERAL(15, 198, 4), // "maxS"
QT_MOC_LITERAL(16, 203, 4), // "minV"
QT_MOC_LITERAL(17, 208, 4), // "maxV"
QT_MOC_LITERAL(18, 213, 12), // "SetThreshold"
QT_MOC_LITERAL(19, 226, 5), // "value"
QT_MOC_LITERAL(20, 232, 13), // "GetObjectInfo"
QT_MOC_LITERAL(21, 246, 1), // "x"
QT_MOC_LITERAL(22, 248, 1), // "y"
QT_MOC_LITERAL(23, 250, 1), // "h"
QT_MOC_LITERAL(24, 252, 1), // "w"
QT_MOC_LITERAL(25, 254, 16), // "GetProcessRegion"
QT_MOC_LITERAL(26, 271, 1), // "a"
QT_MOC_LITERAL(27, 273, 1), // "b"
QT_MOC_LITERAL(28, 275, 1), // "c"
QT_MOC_LITERAL(29, 277, 1), // "d"
QT_MOC_LITERAL(30, 279, 11), // "GetDistance"
QT_MOC_LITERAL(31, 291, 8), // "distance"
QT_MOC_LITERAL(32, 300, 13), // "GetCalibPoint"
QT_MOC_LITERAL(33, 314, 11), // "SwitchLayer"
QT_MOC_LITERAL(34, 326, 19), // "changeAxisDirection"
QT_MOC_LITERAL(35, 346, 20) // "CalConvenyorPosition"

    },
    "ImageProcesser\0ObjectValueChanged\0\0"
    "std::vector<cv::RotatedRect>\0"
    "ObjectContainer\0LoadTestImage\0LoadCamera\0"
    "CaptureAnImageFromCamera\0UpdateCameraScreen\0"
    "SaveFPS\0OpenParameterPanel\0SetHSV\0"
    "minH\0maxH\0minS\0maxS\0minV\0maxV\0"
    "SetThreshold\0value\0GetObjectInfo\0x\0y\0"
    "h\0w\0GetProcessRegion\0a\0b\0c\0d\0GetDistance\0"
    "distance\0GetCalibPoint\0SwitchLayer\0"
    "changeAxisDirection\0CalConvenyorPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageProcesser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   97,    2, 0x0a /* Public */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    0,   99,    2, 0x0a /* Public */,
       8,    0,  100,    2, 0x0a /* Public */,
       9,    0,  101,    2, 0x0a /* Public */,
      10,    0,  102,    2, 0x0a /* Public */,
      11,    6,  103,    2, 0x0a /* Public */,
      18,    1,  116,    2, 0x0a /* Public */,
      20,    4,  119,    2, 0x0a /* Public */,
      25,    4,  128,    2, 0x0a /* Public */,
      30,    1,  137,    2, 0x0a /* Public */,
      32,    2,  140,    2, 0x0a /* Public */,
      33,    0,  145,    2, 0x0a /* Public */,
      34,    0,  146,    2, 0x0a /* Public */,
      35,    0,  147,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   12,   13,   14,   15,   16,   17,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   21,   22,   23,   24,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QPoint,   26,   27,   28,   29,
    QMetaType::Void, QMetaType::Int,   31,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   21,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ImageProcesser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageProcesser *_t = static_cast<ImageProcesser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ObjectValueChanged((*reinterpret_cast< std::vector<cv::RotatedRect>(*)>(_a[1]))); break;
        case 1: _t->LoadTestImage(); break;
        case 2: _t->LoadCamera(); break;
        case 3: _t->CaptureAnImageFromCamera(); break;
        case 4: _t->UpdateCameraScreen(); break;
        case 5: _t->SaveFPS(); break;
        case 6: _t->OpenParameterPanel(); break;
        case 7: _t->SetHSV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 8: _t->SetThreshold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->GetObjectInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 10: _t->GetProcessRegion((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2])),(*reinterpret_cast< QPoint(*)>(_a[3])),(*reinterpret_cast< QPoint(*)>(_a[4]))); break;
        case 11: _t->GetDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->GetCalibPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->SwitchLayer(); break;
        case 14: _t->changeAxisDirection(); break;
        case 15: _t->CalConvenyorPosition(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ImageProcesser::*_t)(std::vector<cv::RotatedRect> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ImageProcesser::ObjectValueChanged)) {
                *result = 0;
                return;
            }
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ImageProcesser::ObjectValueChanged(std::vector<cv::RotatedRect> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
