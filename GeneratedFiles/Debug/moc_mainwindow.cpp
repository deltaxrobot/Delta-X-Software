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
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[60];
    char stringdata0[926];
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
QT_MOC_LITERAL(18, 294, 14), // "UpdateVelocity"
QT_MOC_LITERAL(19, 309, 11), // "UpdateAccel"
QT_MOC_LITERAL(20, 321, 18), // "AdjustGripperAngle"
QT_MOC_LITERAL(21, 340, 5), // "angle"
QT_MOC_LITERAL(22, 346, 4), // "Grip"
QT_MOC_LITERAL(23, 351, 7), // "SetPump"
QT_MOC_LITERAL(24, 359, 5), // "value"
QT_MOC_LITERAL(25, 365, 8), // "SetLaser"
QT_MOC_LITERAL(26, 374, 4), // "Home"
QT_MOC_LITERAL(27, 379, 23), // "UpdateConvenyorPosition"
QT_MOC_LITERAL(28, 403, 20), // "DisplayGcodeVariable"
QT_MOC_LITERAL(29, 424, 20), // "QList<GcodeVariable>"
QT_MOC_LITERAL(30, 445, 14), // "gcodeVariables"
QT_MOC_LITERAL(31, 460, 17), // "SetConvenyorSpeed"
QT_MOC_LITERAL(32, 478, 20), // "GetConvenyorPosition"
QT_MOC_LITERAL(33, 499, 34), // "TurnEnoughConvenyorPositionGe..."
QT_MOC_LITERAL(34, 534, 12), // "AddGcodeLine"
QT_MOC_LITERAL(35, 547, 20), // "ChangeGcodeParameter"
QT_MOC_LITERAL(36, 568, 15), // "ConnectConveyor"
QT_MOC_LITERAL(37, 584, 15), // "SetConveyorMode"
QT_MOC_LITERAL(38, 600, 4), // "mode"
QT_MOC_LITERAL(39, 605, 12), // "MoveConveyor"
QT_MOC_LITERAL(40, 618, 14), // "ConnectSliding"
QT_MOC_LITERAL(41, 633, 13), // "GoHomeSliding"
QT_MOC_LITERAL(42, 647, 14), // "DisableSliding"
QT_MOC_LITERAL(43, 662, 15), // "SetSlidingSpeed"
QT_MOC_LITERAL(44, 678, 18), // "SetSlidingPosition"
QT_MOC_LITERAL(45, 697, 16), // "TerminalTransmit"
QT_MOC_LITERAL(46, 714, 16), // "PrintReceiveData"
QT_MOC_LITERAL(47, 731, 3), // "msg"
QT_MOC_LITERAL(48, 735, 15), // "NoticeConnected"
QT_MOC_LITERAL(49, 751, 14), // "RunSmartEditor"
QT_MOC_LITERAL(50, 766, 20), // "StandardFormatEditor"
QT_MOC_LITERAL(51, 787, 18), // "OpenGcodeReference"
QT_MOC_LITERAL(52, 806, 16), // "ConfigConnection"
QT_MOC_LITERAL(53, 823, 20), // "ChangeDeltaDashboard"
QT_MOC_LITERAL(54, 844, 5), // "index"
QT_MOC_LITERAL(55, 850, 17), // "SelectTrueTabName"
QT_MOC_LITERAL(56, 868, 15), // "FinishedRequest"
QT_MOC_LITERAL(57, 884, 14), // "QNetworkReply*"
QT_MOC_LITERAL(58, 899, 5), // "reply"
QT_MOC_LITERAL(59, 905, 20) // "ExportBlocklyToGcode"

    },
    "MainWindow\0ConnectDeltaRobot\0\0"
    "AddNewProgram\0SaveProgram\0ExecuteProgram\0"
    "ExecuteSelectPrograms\0ExecuteCurrentLine\0"
    "UpdateZLineEditValue\0z\0UpdateWLineEditValue\0"
    "w\0UpdateDeltaPositionFromLineEditValue\0"
    "UpdatePositionFrom2DControl\0x\0y\0"
    "UpdatePositionControl\0"
    "UpdateGlobalHomePositionValueAndControlValue\0"
    "UpdateVelocity\0UpdateAccel\0"
    "AdjustGripperAngle\0angle\0Grip\0SetPump\0"
    "value\0SetLaser\0Home\0UpdateConvenyorPosition\0"
    "DisplayGcodeVariable\0QList<GcodeVariable>\0"
    "gcodeVariables\0SetConvenyorSpeed\0"
    "GetConvenyorPosition\0"
    "TurnEnoughConvenyorPositionGetting\0"
    "AddGcodeLine\0ChangeGcodeParameter\0"
    "ConnectConveyor\0SetConveyorMode\0mode\0"
    "MoveConveyor\0ConnectSliding\0GoHomeSliding\0"
    "DisableSliding\0SetSlidingSpeed\0"
    "SetSlidingPosition\0TerminalTransmit\0"
    "PrintReceiveData\0msg\0NoticeConnected\0"
    "RunSmartEditor\0StandardFormatEditor\0"
    "OpenGcodeReference\0ConfigConnection\0"
    "ChangeDeltaDashboard\0index\0SelectTrueTabName\0"
    "FinishedRequest\0QNetworkReply*\0reply\0"
    "ExportBlocklyToGcode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      45,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  239,    2, 0x08 /* Private */,
       3,    0,  240,    2, 0x08 /* Private */,
       4,    0,  241,    2, 0x08 /* Private */,
       5,    0,  242,    2, 0x08 /* Private */,
       6,    0,  243,    2, 0x08 /* Private */,
       7,    0,  244,    2, 0x08 /* Private */,
       8,    1,  245,    2, 0x08 /* Private */,
      10,    1,  248,    2, 0x08 /* Private */,
      12,    0,  251,    2, 0x08 /* Private */,
      13,    4,  252,    2, 0x08 /* Private */,
      16,    4,  261,    2, 0x08 /* Private */,
      17,    4,  270,    2, 0x08 /* Private */,
      18,    0,  279,    2, 0x08 /* Private */,
      19,    0,  280,    2, 0x08 /* Private */,
      20,    1,  281,    2, 0x08 /* Private */,
      22,    0,  284,    2, 0x08 /* Private */,
      23,    1,  285,    2, 0x08 /* Private */,
      25,    1,  288,    2, 0x08 /* Private */,
      26,    0,  291,    2, 0x08 /* Private */,
      27,    2,  292,    2, 0x08 /* Private */,
      28,    1,  297,    2, 0x08 /* Private */,
      31,    0,  300,    2, 0x08 /* Private */,
      32,    0,  301,    2, 0x08 /* Private */,
      33,    0,  302,    2, 0x08 /* Private */,
      34,    0,  303,    2, 0x08 /* Private */,
      35,    0,  304,    2, 0x08 /* Private */,
      36,    0,  305,    2, 0x08 /* Private */,
      37,    1,  306,    2, 0x08 /* Private */,
      39,    0,  309,    2, 0x08 /* Private */,
      40,    0,  310,    2, 0x08 /* Private */,
      41,    0,  311,    2, 0x08 /* Private */,
      42,    0,  312,    2, 0x08 /* Private */,
      43,    0,  313,    2, 0x08 /* Private */,
      44,    0,  314,    2, 0x08 /* Private */,
      45,    0,  315,    2, 0x08 /* Private */,
      46,    1,  316,    2, 0x08 /* Private */,
      48,    0,  319,    2, 0x08 /* Private */,
      49,    0,  320,    2, 0x08 /* Private */,
      50,    0,  321,    2, 0x08 /* Private */,
      51,    0,  322,    2, 0x08 /* Private */,
      52,    0,  323,    2, 0x08 /* Private */,
      53,    1,  324,    2, 0x08 /* Private */,
      55,    1,  327,    2, 0x08 /* Private */,
      56,    1,  330,    2, 0x08 /* Private */,
      59,    0,  333,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   14,   15,
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   47,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   54,
    QMetaType::Void, QMetaType::Int,   54,
    QMetaType::Void, 0x80000000 | 57,   58,
    QMetaType::Void,

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
        case 12: _t->UpdateVelocity(); break;
        case 13: _t->UpdateAccel(); break;
        case 14: _t->AdjustGripperAngle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->Grip(); break;
        case 16: _t->SetPump((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->SetLaser((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->Home(); break;
        case 19: _t->UpdateConvenyorPosition((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 20: _t->DisplayGcodeVariable((*reinterpret_cast< QList<GcodeVariable>(*)>(_a[1]))); break;
        case 21: _t->SetConvenyorSpeed(); break;
        case 22: _t->GetConvenyorPosition(); break;
        case 23: _t->TurnEnoughConvenyorPositionGetting(); break;
        case 24: _t->AddGcodeLine(); break;
        case 25: _t->ChangeGcodeParameter(); break;
        case 26: _t->ConnectConveyor(); break;
        case 27: _t->SetConveyorMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->MoveConveyor(); break;
        case 29: _t->ConnectSliding(); break;
        case 30: _t->GoHomeSliding(); break;
        case 31: _t->DisableSliding(); break;
        case 32: _t->SetSlidingSpeed(); break;
        case 33: _t->SetSlidingPosition(); break;
        case 34: _t->TerminalTransmit(); break;
        case 35: _t->PrintReceiveData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 36: _t->NoticeConnected(); break;
        case 37: _t->RunSmartEditor(); break;
        case 38: _t->StandardFormatEditor(); break;
        case 39: _t->OpenGcodeReference(); break;
        case 40: _t->ConfigConnection(); break;
        case 41: _t->ChangeDeltaDashboard((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->SelectTrueTabName((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->FinishedRequest((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 44: _t->ExportBlocklyToGcode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 43:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
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
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 45)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 45;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
