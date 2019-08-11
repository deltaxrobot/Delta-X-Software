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
    QByteArrayData data[41];
    char stringdata0[661];
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
QT_MOC_LITERAL(6, 71, 21), // "ExecuteSelectPrograms"
QT_MOC_LITERAL(7, 93, 18), // "ExecuteCurrentLine"
QT_MOC_LITERAL(8, 112, 20), // "UpdateZLineEditValue"
QT_MOC_LITERAL(9, 133, 1), // "z"
QT_MOC_LITERAL(10, 135, 20), // "UpdateWLineEditValue"
QT_MOC_LITERAL(11, 156, 1), // "w"
QT_MOC_LITERAL(12, 158, 36), // "UpdateDeltaPositionFromLineEd..."
QT_MOC_LITERAL(13, 195, 27), // "UpdatePositionFrom2DControl"
QT_MOC_LITERAL(14, 223, 1), // "x"
QT_MOC_LITERAL(15, 225, 1), // "y"
QT_MOC_LITERAL(16, 227, 21), // "UpdatePositionControl"
QT_MOC_LITERAL(17, 249, 44), // "UpdateGlobalHomePositionValue..."
QT_MOC_LITERAL(18, 294, 4), // "Grip"
QT_MOC_LITERAL(19, 299, 7), // "SetPump"
QT_MOC_LITERAL(20, 307, 5), // "value"
QT_MOC_LITERAL(21, 313, 4), // "Home"
QT_MOC_LITERAL(22, 318, 23), // "UpdateConvenyorPosition"
QT_MOC_LITERAL(23, 342, 20), // "DisplayGcodeVariable"
QT_MOC_LITERAL(24, 363, 20), // "QList<GcodeVariable>"
QT_MOC_LITERAL(25, 384, 14), // "gcodeVariables"
QT_MOC_LITERAL(26, 399, 17), // "SetConvenyorSpeed"
QT_MOC_LITERAL(27, 417, 20), // "GetConvenyorPosition"
QT_MOC_LITERAL(28, 438, 34), // "TurnEnoughConvenyorPositionGe..."
QT_MOC_LITERAL(29, 473, 12), // "AddGcodeLine"
QT_MOC_LITERAL(30, 486, 20), // "ChangeGcodeParameter"
QT_MOC_LITERAL(31, 507, 16), // "TerminalTransmit"
QT_MOC_LITERAL(32, 524, 16), // "PrintReceiveData"
QT_MOC_LITERAL(33, 541, 3), // "msg"
QT_MOC_LITERAL(34, 545, 15), // "NoticeConnected"
QT_MOC_LITERAL(35, 561, 14), // "RunSmartEditor"
QT_MOC_LITERAL(36, 576, 20), // "StandardFormatEditor"
QT_MOC_LITERAL(37, 597, 18), // "OpenGcodeReference"
QT_MOC_LITERAL(38, 616, 20), // "ChangeDeltaDashboard"
QT_MOC_LITERAL(39, 637, 5), // "index"
QT_MOC_LITERAL(40, 643, 17) // "SelectTrueTabName"

    },
    "MainWindow\0ConnectDeltaRobot\0\0"
    "AddNewProgram\0SaveProgram\0ExecuteProgram\0"
    "ExecuteSelectPrograms\0ExecuteCurrentLine\0"
    "UpdateZLineEditValue\0z\0UpdateWLineEditValue\0"
    "w\0UpdateDeltaPositionFromLineEditValue\0"
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
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  164,    2, 0x08 /* Private */,
       3,    0,  165,    2, 0x08 /* Private */,
       4,    0,  166,    2, 0x08 /* Private */,
       5,    0,  167,    2, 0x08 /* Private */,
       6,    0,  168,    2, 0x08 /* Private */,
       7,    0,  169,    2, 0x08 /* Private */,
       8,    1,  170,    2, 0x08 /* Private */,
      10,    1,  173,    2, 0x08 /* Private */,
      12,    0,  176,    2, 0x08 /* Private */,
      13,    4,  177,    2, 0x08 /* Private */,
      16,    4,  186,    2, 0x08 /* Private */,
      17,    4,  195,    2, 0x08 /* Private */,
      18,    0,  204,    2, 0x08 /* Private */,
      19,    1,  205,    2, 0x08 /* Private */,
      21,    0,  208,    2, 0x08 /* Private */,
      22,    2,  209,    2, 0x08 /* Private */,
      23,    1,  214,    2, 0x08 /* Private */,
      26,    0,  217,    2, 0x08 /* Private */,
      27,    0,  218,    2, 0x08 /* Private */,
      28,    0,  219,    2, 0x08 /* Private */,
      29,    0,  220,    2, 0x08 /* Private */,
      30,    0,  221,    2, 0x08 /* Private */,
      31,    0,  222,    2, 0x08 /* Private */,
      32,    1,  223,    2, 0x08 /* Private */,
      34,    0,  226,    2, 0x08 /* Private */,
      35,    0,  227,    2, 0x08 /* Private */,
      36,    0,  228,    2, 0x08 /* Private */,
      37,    0,  229,    2, 0x08 /* Private */,
      38,    1,  230,    2, 0x08 /* Private */,
      40,    1,  233,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   14,   15,    9,   11,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   14,   15,    9,   11,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float, QMetaType::Float,   14,   15,    9,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   14,   15,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,

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
        case 4: _t->ExecuteSelectPrograms(); break;
        case 5: _t->ExecuteCurrentLine(); break;
        case 6: _t->UpdateZLineEditValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->UpdateWLineEditValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->UpdateDeltaPositionFromLineEditValue(); break;
        case 9: _t->UpdatePositionFrom2DControl((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 10: _t->UpdatePositionControl((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 11: _t->UpdateGlobalHomePositionValueAndControlValue((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4]))); break;
        case 12: _t->Grip(); break;
        case 13: _t->SetPump((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->Home(); break;
        case 15: _t->UpdateConvenyorPosition((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 16: _t->DisplayGcodeVariable((*reinterpret_cast< QList<GcodeVariable>(*)>(_a[1]))); break;
        case 17: _t->SetConvenyorSpeed(); break;
        case 18: _t->GetConvenyorPosition(); break;
        case 19: _t->TurnEnoughConvenyorPositionGetting(); break;
        case 20: _t->AddGcodeLine(); break;
        case 21: _t->ChangeGcodeParameter(); break;
        case 22: _t->TerminalTransmit(); break;
        case 23: _t->PrintReceiveData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->NoticeConnected(); break;
        case 25: _t->RunSmartEditor(); break;
        case 26: _t->StandardFormatEditor(); break;
        case 27: _t->OpenGcodeReference(); break;
        case 28: _t->ChangeDeltaDashboard((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->SelectTrueTabName((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 30;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
