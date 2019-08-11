/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeltaXDashboard_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeltaXDashboard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeltaXDashboard_t qt_meta_stringdata_DeltaXDashboard = {
    {
QT_MOC_LITERAL(0, 0, 15) // "DeltaXDashboard"

    },
    "DeltaXDashboard"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeltaXDashboard[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void DeltaXDashboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject DeltaXDashboard::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DeltaXDashboard.data,
      qt_meta_data_DeltaXDashboard,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DeltaXDashboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeltaXDashboard::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DeltaXDashboard.stringdata0))
        return static_cast<void*>(const_cast< DeltaXDashboard*>(this));
    return QObject::qt_metacast(_clname);
}

int DeltaXDashboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[40];
    char stringdata0[639];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "ConnectDeltaRobot"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 13), // "AddNewProgram"
QT_MOC_LITERAL(4, 44, 11), // "SaveProgram"
QT_MOC_LITERAL(5, 56, 14), // "ExecuteProgram"
QT_MOC_LITERAL(6, 71, 18), // "ExecuteCurrentLine"
QT_MOC_LITERAL(7, 90, 20), // "UpdateZLineEditValue"
QT_MOC_LITERAL(8, 111, 1), // "z"
QT_MOC_LITERAL(9, 113, 20), // "UpdateWLineEditValue"
QT_MOC_LITERAL(10, 134, 1), // "w"
QT_MOC_LITERAL(11, 136, 36), // "UpdateDeltaPositionFromLineEd..."
QT_MOC_LITERAL(12, 173, 27), // "UpdatePositionFrom2DControl"
QT_MOC_LITERAL(13, 201, 1), // "x"
QT_MOC_LITERAL(14, 203, 1), // "y"
QT_MOC_LITERAL(15, 205, 21), // "UpdatePositionControl"
QT_MOC_LITERAL(16, 227, 44), // "UpdateGlobalHomePositionValue..."
QT_MOC_LITERAL(17, 272, 4), // "Grip"
QT_MOC_LITERAL(18, 277, 7), // "SetPump"
QT_MOC_LITERAL(19, 285, 5), // "value"
QT_MOC_LITERAL(20, 291, 4), // "Home"
QT_MOC_LITERAL(21, 296, 23), // "UpdateConvenyorPosition"
QT_MOC_LITERAL(22, 320, 20), // "DisplayGcodeVariable"
QT_MOC_LITERAL(23, 341, 20), // "QList<GcodeVariable>"
QT_MOC_LITERAL(24, 362, 14), // "gcodeVariables"
QT_MOC_LITERAL(25, 377, 17), // "SetConvenyorSpeed"
QT_MOC_LITERAL(26, 395, 20), // "GetConvenyorPosition"
QT_MOC_LITERAL(27, 416, 34), // "TurnEnoughConvenyorPositionGe..."
QT_MOC_LITERAL(28, 451, 12), // "AddGcodeLine"
QT_MOC_LITERAL(29, 464, 20), // "ChangeGcodeParameter"
QT_MOC_LITERAL(30, 485, 16), // "TerminalTransmit"
QT_MOC_LITERAL(31, 502, 16), // "PrintReceiveData"
QT_MOC_LITERAL(32, 519, 3), // "msg"
QT_MOC_LITERAL(33, 523, 15), // "NoticeConnected"
QT_MOC_LITERAL(34, 539, 14), // "RunSmartEditor"
QT_MOC_LITERAL(35, 554, 20), // "StandardFormatEditor"
QT_MOC_LITERAL(36, 575, 18), // "OpenGcodeReference"
QT_MOC_LITERAL(37, 594, 20), // "ChangeDeltaDashboard"
QT_MOC_LITERAL(38, 615, 5), // "index"
QT_MOC_LITERAL(39, 621, 17) // "SelectTrueTabName"

    },
    "MainWindow\0ConnectDeltaRobot\0\0"
    "AddNewProgram\0SaveProgram\0ExecuteProgram\0"
    "ExecuteCurrentLine\0UpdateZLineEditValue\0"
    "z\0UpdateWLineEditValue\0w\0"
    "UpdateDeltaPositionFromLineEditValue\0"
    "UpdatePositionFrom2DControl\0x\0y\0"
    "UpdatePositionControl\0"
    "UpdateGlobalHomePositionValueAndControlValue\0"
    "Grip\0SetPump\0value\0Home\0UpdateConvenyorPosition\0"
    "DisplayGcodeVariable\0QList<GcodeVariable>\0"
    "gcodeVariables\0SetConvenyorSpeed\0"
    "GetConvenyorPosition\0"
    "TurnEnoughConvenyorPositionGetting\0"
    "AddGcodeLine\0ChangeGcodeParameter\0"
    "TerminalTransmit\0PrintReceiveData\0msg\0"
    "NoticeConnected\0RunSmartEditor\0"
    "StandardFormatEditor\0OpenGcodeReference\0"
    "ChangeDeltaDashboard\0index\0SelectTrueTabName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  159,    2, 0x08 /* Private */,
       3,    0,  160,    2, 0x08 /* Private */,
       4,    0,  161,    2, 0x08 /* Private */,
       5,    0,  162,    2, 0x08 /* Private */,
       6,    0,  163,    2, 0x08 /* Private */,
       7,    1,  164,    2, 0x08 /* Private */,
       9,    1,  167,    2, 0x08 /* Private */,
      11,    0,  170,    2, 0x08 /* Private */,
      12,    4,  171,    2, 0x08 /* Private */,
      15,    4,  180,    2, 0x08 /* Private */,
      16,    4,  189,    2, 0x08 /* Private */,
      17,    0,  198,    2, 0x08 /* Private */,
      18,    1,  199,    2, 0x08 /* Private */,
      20,    0,  202,    2, 0x08 /* Private */,
      21,    2,  203,    2, 0x08 /* Private */,
      22,    1,  208,    2, 0x08 /* Private */,
      25,    0,  211,    2, 0x08 /* Private */,
      26,    0,  212,    2, 0x08 /* Private */,
      27,    0,  213,    2, 0x08 /* Private */,
      28,    0,  214,    2, 0x08 /* Private */,
      29,    0,  215,    2, 0x08 /* Private */,
      30,    0,  216,    2, 0x08 /* Private */,
      31,    1,  217,    2, 0x08 /* Private */,
      33,    0,  220,    2, 0x08 /* Private */,
      34,    0,  221,    2, 0x08 /* Private */,
      35,    0,  222,    2, 0x08 /* Private */,
      36,    0,  223,    2, 0x08 /* Private */,
      37,    1,  224,    2, 0x08 /* Private */,
      39,    1,  227,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   13,   14,    8,   10,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   13,   14,    8,   10,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   13,   14,    8,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   13,   14,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ConnectDeltaRobot(); break;
        case 1: _t->AddNewProgram(); break;
        case 2: _t->SaveProgram(); break;
        case 3: _t->ExecuteProgram(); break;
        case 4: _t->ExecuteCurrentLine(); break;
        case 5: _t->UpdateZLineEditValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->UpdateWLineEditValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->UpdateDeltaPositionFromLineEditValue(); break;
        case 8: _t->UpdatePositionFrom2DControl((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 9: _t->UpdatePositionControl((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 10: _t->UpdateGlobalHomePositionValueAndControlValue((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 11: _t->Grip(); break;
        case 12: _t->SetPump((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->Home(); break;
        case 14: _t->UpdateConvenyorPosition((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 15: _t->DisplayGcodeVariable((*reinterpret_cast< QList<GcodeVariable>(*)>(_a[1]))); break;
        case 16: _t->SetConvenyorSpeed(); break;
        case 17: _t->GetConvenyorPosition(); break;
        case 18: _t->TurnEnoughConvenyorPositionGetting(); break;
        case 19: _t->AddGcodeLine(); break;
        case 20: _t->ChangeGcodeParameter(); break;
        case 21: _t->TerminalTransmit(); break;
        case 22: _t->PrintReceiveData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 23: _t->NoticeConnected(); break;
        case 24: _t->RunSmartEditor(); break;
        case 25: _t->StandardFormatEditor(); break;
        case 26: _t->OpenGcodeReference(); break;
        case 27: _t->ChangeDeltaDashboard((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->SelectTrueTabName((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 29;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
