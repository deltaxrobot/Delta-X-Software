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
    QByteArrayData data[24];
    char stringdata0[276];
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
QT_MOC_LITERAL(6, 71, 12), // "UpdateZValue"
QT_MOC_LITERAL(7, 84, 1), // "z"
QT_MOC_LITERAL(8, 86, 19), // "UpdateDeltaPosition"
QT_MOC_LITERAL(9, 106, 19), // "UpdatePositionValue"
QT_MOC_LITERAL(10, 126, 1), // "x"
QT_MOC_LITERAL(11, 128, 1), // "y"
QT_MOC_LITERAL(12, 130, 18), // "UpdateHomePosition"
QT_MOC_LITERAL(13, 149, 4), // "Grip"
QT_MOC_LITERAL(14, 154, 7), // "SetPump"
QT_MOC_LITERAL(15, 162, 5), // "value"
QT_MOC_LITERAL(16, 168, 4), // "Home"
QT_MOC_LITERAL(17, 173, 12), // "AddGcodeLine"
QT_MOC_LITERAL(18, 186, 16), // "TerminalTransmit"
QT_MOC_LITERAL(19, 203, 16), // "PrintReceiveData"
QT_MOC_LITERAL(20, 220, 3), // "msg"
QT_MOC_LITERAL(21, 224, 15), // "NoticeConnected"
QT_MOC_LITERAL(22, 240, 14), // "RunSmartEditor"
QT_MOC_LITERAL(23, 255, 20) // "StandardFormatEditor"

    },
    "MainWindow\0ConnectDeltaRobot\0\0"
    "AddNewProgram\0SaveProgram\0ExecuteProgram\0"
    "UpdateZValue\0z\0UpdateDeltaPosition\0"
    "UpdatePositionValue\0x\0y\0UpdateHomePosition\0"
    "Grip\0SetPump\0value\0Home\0AddGcodeLine\0"
    "TerminalTransmit\0PrintReceiveData\0msg\0"
    "NoticeConnected\0RunSmartEditor\0"
    "StandardFormatEditor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    1,  103,    2, 0x08 /* Private */,
       8,    0,  106,    2, 0x08 /* Private */,
       9,    3,  107,    2, 0x08 /* Private */,
      12,    3,  114,    2, 0x08 /* Private */,
      13,    0,  121,    2, 0x08 /* Private */,
      14,    1,  122,    2, 0x08 /* Private */,
      16,    0,  125,    2, 0x08 /* Private */,
      17,    0,  126,    2, 0x08 /* Private */,
      18,    0,  127,    2, 0x08 /* Private */,
      19,    1,  128,    2, 0x08 /* Private */,
      21,    0,  131,    2, 0x08 /* Private */,
      22,    0,  132,    2, 0x08 /* Private */,
      23,    0,  133,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float,   10,   11,    7,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float,   10,   11,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,
    QMetaType::Void,
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
        case 4: _t->UpdateZValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->UpdateDeltaPosition(); break;
        case 6: _t->UpdatePositionValue((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 7: _t->UpdateHomePosition((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 8: _t->Grip(); break;
        case 9: _t->SetPump((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->Home(); break;
        case 11: _t->AddGcodeLine(); break;
        case 12: _t->TerminalTransmit(); break;
        case 13: _t->PrintReceiveData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->NoticeConnected(); break;
        case 15: _t->RunSmartEditor(); break;
        case 16: _t->StandardFormatEditor(); break;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
