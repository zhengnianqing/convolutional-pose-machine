/****************************************************************************
** Meta object code from reading C++ file 'pose_re.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pose_re.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pose_re.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Pose_Re_t {
    QByteArrayData data[13];
    char stringdata0[131];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Pose_Re_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Pose_Re_t qt_meta_stringdata_Pose_Re = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Pose_Re"
QT_MOC_LITERAL(1, 8, 10), // "send_image"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "cv::Mat"
QT_MOC_LITERAL(4, 28, 12), // "Open_Picture"
QT_MOC_LITERAL(5, 41, 10), // "Begin_Test"
QT_MOC_LITERAL(6, 52, 12), // "Stop_Systeam"
QT_MOC_LITERAL(7, 65, 12), // "testFunction"
QT_MOC_LITERAL(8, 78, 11), // "Save_Result"
QT_MOC_LITERAL(9, 90, 15), // "receive_message"
QT_MOC_LITERAL(10, 106, 7), // "shuaxin"
QT_MOC_LITERAL(11, 114, 12), // "return_Image"
QT_MOC_LITERAL(12, 127, 3) // "num"

    },
    "Pose_Re\0send_image\0\0cv::Mat\0Open_Picture\0"
    "Begin_Test\0Stop_Systeam\0testFunction\0"
    "Save_Result\0receive_message\0shuaxin\0"
    "return_Image\0num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Pose_Re[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   57,    2, 0x0a /* Public */,
       5,    0,   58,    2, 0x0a /* Public */,
       6,    0,   59,    2, 0x0a /* Public */,
       7,    0,   60,    2, 0x0a /* Public */,
       8,    0,   61,    2, 0x0a /* Public */,
       9,    0,   62,    2, 0x0a /* Public */,
      10,    2,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,   11,   12,

       0        // eod
};

void Pose_Re::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Pose_Re *_t = static_cast<Pose_Re *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_image((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        case 1: _t->Open_Picture(); break;
        case 2: _t->Begin_Test(); break;
        case 3: _t->Stop_Systeam(); break;
        case 4: _t->testFunction(); break;
        case 5: _t->Save_Result(); break;
        case 6: _t->receive_message(); break;
        case 7: _t->shuaxin((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Pose_Re::*_t)(cv::Mat );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Pose_Re::send_image)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Pose_Re::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Pose_Re.data,
      qt_meta_data_Pose_Re,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Pose_Re::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Pose_Re::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Pose_Re.stringdata0))
        return static_cast<void*>(const_cast< Pose_Re*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Pose_Re::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Pose_Re::send_image(cv::Mat _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
