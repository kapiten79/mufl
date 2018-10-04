/****************************************************************************
** Meta object code from reading C++ file 'paneltablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../widgets/paneltablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paneltablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PanelTableWidget_t {
    QByteArrayData data[19];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PanelTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PanelTableWidget_t qt_meta_stringdata_PanelTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PanelTableWidget"
QT_MOC_LITERAL(1, 17, 10), // "createFile"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "editFile"
QT_MOC_LITERAL(4, 38, 8), // "fileName"
QT_MOC_LITERAL(5, 47, 12), // "enterPressed"
QT_MOC_LITERAL(6, 60, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(7, 78, 4), // "item"
QT_MOC_LITERAL(8, 83, 11), // "changePanel"
QT_MOC_LITERAL(9, 95, 10), // "createPath"
QT_MOC_LITERAL(10, 106, 10), // "removePath"
QT_MOC_LITERAL(11, 117, 8), // "pathName"
QT_MOC_LITERAL(12, 126, 14), // "copyPathOrFile"
QT_MOC_LITERAL(13, 141, 18), // "p_selectedFileList"
QT_MOC_LITERAL(14, 160, 14), // "movePathOrFile"
QT_MOC_LITERAL(15, 175, 17), // "setMinimizeWindow"
QT_MOC_LITERAL(16, 193, 14), // "setCloseWindow"
QT_MOC_LITERAL(17, 208, 13), // "insertPressed"
QT_MOC_LITERAL(18, 222, 14) // "showFindWindow"

    },
    "PanelTableWidget\0createFile\0\0editFile\0"
    "fileName\0enterPressed\0QTableWidgetItem*\0"
    "item\0changePanel\0createPath\0removePath\0"
    "pathName\0copyPathOrFile\0p_selectedFileList\0"
    "movePathOrFile\0setMinimizeWindow\0"
    "setCloseWindow\0insertPressed\0"
    "showFindWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       5,    1,   78,    2, 0x06 /* Public */,
       8,    0,   81,    2, 0x06 /* Public */,
       9,    0,   82,    2, 0x06 /* Public */,
      10,    1,   83,    2, 0x06 /* Public */,
      12,    1,   86,    2, 0x06 /* Public */,
      14,    1,   89,    2, 0x06 /* Public */,
      15,    0,   92,    2, 0x06 /* Public */,
      16,    0,   93,    2, 0x06 /* Public */,
      17,    0,   94,    2, 0x06 /* Public */,
      18,    0,   95,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QStringList,   13,
    QMetaType::Void, QMetaType::QStringList,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PanelTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PanelTableWidget *_t = static_cast<PanelTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createFile(); break;
        case 1: _t->editFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->enterPressed((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->changePanel(); break;
        case 4: _t->createPath(); break;
        case 5: _t->removePath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->copyPathOrFile((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 7: _t->movePathOrFile((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 8: _t->setMinimizeWindow(); break;
        case 9: _t->setCloseWindow(); break;
        case 10: _t->insertPressed(); break;
        case 11: _t->showFindWindow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PanelTableWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::createFile)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::editFile)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)(QTableWidgetItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::enterPressed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::changePanel)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::createPath)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::removePath)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::copyPathOrFile)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::movePathOrFile)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::setMinimizeWindow)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::setCloseWindow)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::insertPressed)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (PanelTableWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PanelTableWidget::showFindWindow)) {
                *result = 11;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PanelTableWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_PanelTableWidget.data,
      qt_meta_data_PanelTableWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PanelTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PanelTableWidget.stringdata0))
        return static_cast<void*>(this);
    return QTableWidget::qt_metacast(_clname);
}

int PanelTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void PanelTableWidget::createFile()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PanelTableWidget::editFile(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PanelTableWidget::enterPressed(QTableWidgetItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PanelTableWidget::changePanel()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PanelTableWidget::createPath()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PanelTableWidget::removePath(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PanelTableWidget::copyPathOrFile(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PanelTableWidget::movePathOrFile(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PanelTableWidget::setMinimizeWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void PanelTableWidget::setCloseWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void PanelTableWidget::insertPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void PanelTableWidget::showFindWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
