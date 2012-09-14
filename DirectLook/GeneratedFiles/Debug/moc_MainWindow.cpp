/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Thu 26. Apr 13:22:15 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

using namespace DirectLook;

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      36,   11,   11,   11, 0x08,
      54,   11,   49,   11, 0x08,
      64,   11,   11,   11, 0x08,
      76,   11,   11,   11, 0x08,
      86,   11,   11,   11, 0x08,
      97,   11,   11,   11, 0x08,
     119,   11,   11,   11, 0x08,
     152,  138,   11,   11, 0x08,
     184,  171,   11,   11, 0x08,
     202,   11,   11,   11, 0x08,
     213,   11,   11,   11, 0x08,
     226,   11,   11,   11, 0x08,
     240,   11,   11,   11, 0x08,
     254,   11,   11,   11, 0x08,
     269,   11,   11,   11, 0x08,
     283,   11,   11,   11, 0x08,
     299,   11,   11,   11, 0x08,
     315,   11,   11,   11, 0x08,
     332,   11,   11,   11, 0x08,
     349,   11,   11,   11, 0x08,
     363,  357,   11,   11, 0x08,
     376,  357,   11,   11, 0x08,
     389,  357,   11,   11, 0x08,
     402,   11,   11,   11, 0x08,
     412,   11,   11,   11, 0x08,
     424,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0connectToSensorDevice()\0"
    "disconnect()\0bool\0loadONI()\0unloadONI()\0"
    "set4To3()\0set16To9()\0loadBackgroundImage()\0"
    "switchBackground()\0nearThreshold\0"
    "nearThreshold(int)\0farThreshold\0"
    "farThreshold(int)\0cameraUp()\0cameraDown()\0"
    "cameraReset()\0textureMode()\0sensorUpdate()\0"
    "translateUp()\0translateDown()\0"
    "translateLeft()\0translateRight()\0"
    "translateReset()\0reset()\0angle\0"
    "rotateX(int)\0rotateY(int)\0rotateZ(int)\0"
    "motorUp()\0motorDown()\0motorReset()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->connectToSensorDevice(); break;
        case 1: _t->disconnect(); break;
        case 2: { bool _r = _t->loadONI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->unloadONI(); break;
        case 4: _t->set4To3(); break;
        case 5: _t->set16To9(); break;
        case 6: _t->loadBackgroundImage(); break;
        case 7: _t->switchBackground(); break;
        case 8: _t->nearThreshold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->farThreshold((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->cameraUp(); break;
        case 11: _t->cameraDown(); break;
        case 12: _t->cameraReset(); break;
        case 13: _t->textureMode(); break;
        case 14: _t->sensorUpdate(); break;
        case 15: _t->translateUp(); break;
        case 16: _t->translateDown(); break;
        case 17: _t->translateLeft(); break;
        case 18: _t->translateRight(); break;
        case 19: _t->translateReset(); break;
        case 20: _t->reset(); break;
        case 21: _t->rotateX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->rotateY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->rotateZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->motorUp(); break;
        case 25: _t->motorDown(); break;
        case 26: _t->motorReset(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
