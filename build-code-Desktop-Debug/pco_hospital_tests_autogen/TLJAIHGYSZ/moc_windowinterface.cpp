/****************************************************************************
** Meta object code from reading C++ file 'windowinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../code/src/internal/windowinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'windowinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WindowInterface_t {
    QByteArrayData data[14];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WindowInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WindowInterface_t qt_meta_stringdata_WindowInterface = {
    {
QT_MOC_LITERAL(0, 0, 15), // "WindowInterface"
QT_MOC_LITERAL(1, 16, 21), // "sig_consoleAppendText"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 9), // "consoleId"
QT_MOC_LITERAL(4, 49, 4), // "text"
QT_MOC_LITERAL(5, 54, 14), // "sig_updateFund"
QT_MOC_LITERAL(6, 69, 2), // "id"
QT_MOC_LITERAL(7, 72, 8), // "new_fund"
QT_MOC_LITERAL(8, 81, 15), // "sig_updateStock"
QT_MOC_LITERAL(9, 97, 23), // "std::map<ItemType,int>*"
QT_MOC_LITERAL(10, 121, 6), // "stocks"
QT_MOC_LITERAL(11, 128, 12), // "sig_set_link"
QT_MOC_LITERAL(12, 141, 4), // "from"
QT_MOC_LITERAL(13, 146, 2) // "to"

    },
    "WindowInterface\0sig_consoleAppendText\0"
    "\0consoleId\0text\0sig_updateFund\0id\0"
    "new_fund\0sig_updateStock\0"
    "std::map<ItemType,int>*\0stocks\0"
    "sig_set_link\0from\0to"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WindowInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    2,   39,    2, 0x06 /* Public */,
       8,    2,   44,    2, 0x06 /* Public */,
      11,    2,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    6,    7,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9,    6,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,

       0        // eod
};

void WindowInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WindowInterface *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sig_consoleAppendText((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->sig_updateFund((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 2: _t->sig_updateStock((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::map<ItemType,int>*(*)>(_a[2]))); break;
        case 3: _t->sig_set_link((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WindowInterface::*)(unsigned int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowInterface::sig_consoleAppendText)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WindowInterface::*)(unsigned int , unsigned  );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowInterface::sig_updateFund)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WindowInterface::*)(unsigned int , std::map<ItemType,int> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowInterface::sig_updateStock)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WindowInterface::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowInterface::sig_set_link)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WindowInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WindowInterface.data,
    qt_meta_data_WindowInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WindowInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WindowInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WindowInterface.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IWindowInterface"))
        return static_cast< IWindowInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int WindowInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void WindowInterface::sig_consoleAppendText(unsigned int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WindowInterface::sig_updateFund(unsigned int _t1, unsigned  _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WindowInterface::sig_updateStock(unsigned int _t1, std::map<ItemType,int> * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WindowInterface::sig_set_link(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
