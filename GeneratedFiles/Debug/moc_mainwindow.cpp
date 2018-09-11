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
    QByteArrayData data[22];
    char stringdata0[270];
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
QT_MOC_LITERAL(3, 30, 18), // "UpdateCameraScreen"
QT_MOC_LITERAL(4, 49, 13), // "AddNewProgram"
QT_MOC_LITERAL(5, 63, 11), // "SaveProgram"
QT_MOC_LITERAL(6, 75, 14), // "ExecuteProgram"
QT_MOC_LITERAL(7, 90, 12), // "UpdateZValue"
QT_MOC_LITERAL(8, 103, 1), // "z"
QT_MOC_LITERAL(9, 105, 19), // "UpdateDeltaPosition"
QT_MOC_LITERAL(10, 125, 19), // "UpdatePositionValue"
QT_MOC_LITERAL(11, 145, 1), // "x"
QT_MOC_LITERAL(12, 147, 1), // "y"
QT_MOC_LITERAL(13, 149, 4), // "Home"
QT_MOC_LITERAL(14, 154, 12), // "AddGcodeLine"
QT_MOC_LITERAL(15, 167, 16), // "TerminalTransmit"
QT_MOC_LITERAL(16, 184, 16), // "PrintReceiveData"
QT_MOC_LITERAL(17, 201, 3), // "msg"
QT_MOC_LITERAL(18, 205, 15), // "NoticeConnected"
QT_MOC_LITERAL(19, 221, 12), // "OpenHSVPanel"
QT_MOC_LITERAL(20, 234, 14), // "RunSmartEditor"
QT_MOC_LITERAL(21, 249, 20) // "StandardFormatEditor"

    },
    "MainWindow\0ConnectDeltaRobot\0\0"
    "UpdateCameraScreen\0AddNewProgram\0"
    "SaveProgram\0ExecuteProgram\0UpdateZValue\0"
    "z\0UpdateDeltaPosition\0UpdatePositionValue\0"
    "x\0y\0Home\0AddGcodeLine\0TerminalTransmit\0"
    "PrintReceiveData\0msg\0NoticeConnected\0"
    "OpenHSVPanel\0RunSmartEditor\0"
    "StandardFormatEditor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    1,   99,    2, 0x08 /* Private */,
       9,    0,  102,    2, 0x08 /* Private */,
      10,    3,  103,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    1,  113,    2, 0x08 /* Private */,
      18,    0,  116,    2, 0x08 /* Private */,
      19,    0,  117,    2, 0x08 /* Private */,
      20,    0,  118,    2, 0x08 /* Private */,
      21,    0,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float,   11,   12,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void,
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
        case 1: _t->UpdateCameraScreen(); break;
        case 2: _t->AddNewProgram(); break;
        case 3: _t->SaveProgram(); break;
        case 4: _t->ExecuteProgram(); break;
        case 5: _t->UpdateZValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->UpdateDeltaPosition(); break;
        case 7: _t->UpdatePositionValue((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 8: _t->Home(); break;
        case 9: _t->AddGcodeLine(); break;
        case 10: _t->TerminalTransmit(); break;
        case 11: _t->PrintReceiveData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->NoticeConnected(); break;
        case 13: _t->OpenHSVPanel(); break;
        case 14: _t->RunSmartEditor(); break;
        case 15: _t->StandardFormatEditor(); break;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
