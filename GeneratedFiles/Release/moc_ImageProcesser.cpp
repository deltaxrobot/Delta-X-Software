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
    QByteArrayData data[57];
    char stringdata0[624];
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
QT_MOC_LITERAL(7, 105, 13), // "CaptureCamera"
QT_MOC_LITERAL(8, 119, 11), // "PauseCamera"
QT_MOC_LITERAL(9, 131, 10), // "PlayCamera"
QT_MOC_LITERAL(10, 142, 5), // "state"
QT_MOC_LITERAL(11, 148, 12), // "ResumeCamera"
QT_MOC_LITERAL(12, 161, 18), // "UpdateCameraScreen"
QT_MOC_LITERAL(13, 180, 7), // "SaveFPS"
QT_MOC_LITERAL(14, 188, 18), // "OpenParameterPanel"
QT_MOC_LITERAL(15, 207, 6), // "SetHSV"
QT_MOC_LITERAL(16, 214, 4), // "minH"
QT_MOC_LITERAL(17, 219, 4), // "maxH"
QT_MOC_LITERAL(18, 224, 4), // "minS"
QT_MOC_LITERAL(19, 229, 4), // "maxS"
QT_MOC_LITERAL(20, 234, 4), // "minV"
QT_MOC_LITERAL(21, 239, 4), // "maxV"
QT_MOC_LITERAL(22, 244, 12), // "SetThreshold"
QT_MOC_LITERAL(23, 257, 5), // "value"
QT_MOC_LITERAL(24, 263, 13), // "GetObjectInfo"
QT_MOC_LITERAL(25, 277, 1), // "x"
QT_MOC_LITERAL(26, 279, 1), // "y"
QT_MOC_LITERAL(27, 281, 1), // "l"
QT_MOC_LITERAL(28, 283, 1), // "w"
QT_MOC_LITERAL(29, 285, 20), // "GetPerspectivePoints"
QT_MOC_LITERAL(30, 306, 1), // "a"
QT_MOC_LITERAL(31, 308, 1), // "b"
QT_MOC_LITERAL(32, 310, 1), // "c"
QT_MOC_LITERAL(33, 312, 1), // "d"
QT_MOC_LITERAL(34, 314, 14), // "GetProcessArea"
QT_MOC_LITERAL(35, 329, 11), // "processArea"
QT_MOC_LITERAL(36, 341, 12), // "GetCalibLine"
QT_MOC_LITERAL(37, 354, 2), // "p1"
QT_MOC_LITERAL(38, 357, 2), // "p2"
QT_MOC_LITERAL(39, 360, 11), // "GetDistance"
QT_MOC_LITERAL(40, 372, 8), // "distance"
QT_MOC_LITERAL(41, 381, 13), // "GetCalibPoint"
QT_MOC_LITERAL(42, 395, 11), // "SwitchLayer"
QT_MOC_LITERAL(43, 407, 11), // "SelectLayer"
QT_MOC_LITERAL(44, 419, 2), // "id"
QT_MOC_LITERAL(45, 422, 19), // "changeAxisDirection"
QT_MOC_LITERAL(46, 442, 24), // "TurnTransformPerspective"
QT_MOC_LITERAL(47, 467, 8), // "isTurnOn"
QT_MOC_LITERAL(48, 476, 16), // "TurnCalibDisplay"
QT_MOC_LITERAL(49, 493, 18), // "ExpandCameraWidget"
QT_MOC_LITERAL(50, 512, 8), // "isExpand"
QT_MOC_LITERAL(51, 521, 16), // "OpenCameraWindow"
QT_MOC_LITERAL(52, 538, 17), // "CloseCameraWindow"
QT_MOC_LITERAL(53, 556, 12), // "UpdateRatios"
QT_MOC_LITERAL(54, 569, 30), // "UpdateObjectPositionOnConveyor"
QT_MOC_LITERAL(55, 600, 11), // "SaveSetting"
QT_MOC_LITERAL(56, 612, 11) // "LoadSetting"

    },
    "ImageProcesser\0ObjectValueChanged\0\0"
    "std::vector<cv::RotatedRect>\0"
    "ObjectContainer\0LoadTestImage\0LoadCamera\0"
    "CaptureCamera\0PauseCamera\0PlayCamera\0"
    "state\0ResumeCamera\0UpdateCameraScreen\0"
    "SaveFPS\0OpenParameterPanel\0SetHSV\0"
    "minH\0maxH\0minS\0maxS\0minV\0maxV\0"
    "SetThreshold\0value\0GetObjectInfo\0x\0y\0"
    "l\0w\0GetPerspectivePoints\0a\0b\0c\0d\0"
    "GetProcessArea\0processArea\0GetCalibLine\0"
    "p1\0p2\0GetDistance\0distance\0GetCalibPoint\0"
    "SwitchLayer\0SelectLayer\0id\0"
    "changeAxisDirection\0TurnTransformPerspective\0"
    "isTurnOn\0TurnCalibDisplay\0ExpandCameraWidget\0"
    "isExpand\0OpenCameraWindow\0CloseCameraWindow\0"
    "UpdateRatios\0UpdateObjectPositionOnConveyor\0"
    "SaveSetting\0LoadSetting"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageProcesser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  169,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  172,    2, 0x0a /* Public */,
       6,    0,  173,    2, 0x0a /* Public */,
       7,    0,  174,    2, 0x0a /* Public */,
       8,    0,  175,    2, 0x0a /* Public */,
       9,    1,  176,    2, 0x0a /* Public */,
      11,    0,  179,    2, 0x0a /* Public */,
      12,    0,  180,    2, 0x0a /* Public */,
      13,    0,  181,    2, 0x0a /* Public */,
      14,    0,  182,    2, 0x0a /* Public */,
      15,    6,  183,    2, 0x0a /* Public */,
      22,    1,  196,    2, 0x0a /* Public */,
      24,    4,  199,    2, 0x0a /* Public */,
      24,    2,  208,    2, 0x0a /* Public */,
      29,    4,  213,    2, 0x0a /* Public */,
      34,    1,  222,    2, 0x0a /* Public */,
      36,    2,  225,    2, 0x0a /* Public */,
      39,    1,  230,    2, 0x0a /* Public */,
      41,    2,  233,    2, 0x0a /* Public */,
      42,    0,  238,    2, 0x0a /* Public */,
      43,    1,  239,    2, 0x0a /* Public */,
      45,    0,  242,    2, 0x0a /* Public */,
      46,    1,  243,    2, 0x0a /* Public */,
      48,    1,  246,    2, 0x0a /* Public */,
      49,    1,  249,    2, 0x0a /* Public */,
      51,    0,  252,    2, 0x0a /* Public */,
      52,    0,  253,    2, 0x0a /* Public */,
      53,    0,  254,    2, 0x0a /* Public */,
      54,    0,  255,    2, 0x0a /* Public */,
      55,    0,  256,    2, 0x0a /* Public */,
      56,    0,  257,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   16,   17,   18,   19,   20,   21,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   25,   26,   27,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   27,   28,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QPoint, QMetaType::QPoint,   30,   31,   32,   33,
    QMetaType::Void, QMetaType::QRect,   35,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint,   37,   38,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   25,   26,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   47,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   50,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 3: _t->CaptureCamera(); break;
        case 4: _t->PauseCamera(); break;
        case 5: _t->PlayCamera((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->ResumeCamera(); break;
        case 7: _t->UpdateCameraScreen(); break;
        case 8: _t->SaveFPS(); break;
        case 9: _t->OpenParameterPanel(); break;
        case 10: _t->SetHSV((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 11: _t->SetThreshold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->GetObjectInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 13: _t->GetObjectInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->GetPerspectivePoints((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2])),(*reinterpret_cast< QPoint(*)>(_a[3])),(*reinterpret_cast< QPoint(*)>(_a[4]))); break;
        case 15: _t->GetProcessArea((*reinterpret_cast< QRect(*)>(_a[1]))); break;
        case 16: _t->GetCalibLine((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 17: _t->GetDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->GetCalibPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 19: _t->SwitchLayer(); break;
        case 20: _t->SelectLayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->changeAxisDirection(); break;
        case 22: _t->TurnTransformPerspective((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->TurnCalibDisplay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->ExpandCameraWidget((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->OpenCameraWindow(); break;
        case 26: _t->CloseCameraWindow(); break;
        case 27: _t->UpdateRatios(); break;
        case 28: _t->UpdateObjectPositionOnConveyor(); break;
        case 29: _t->SaveSetting(); break;
        case 30: _t->LoadSetting(); break;
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
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 31;
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
