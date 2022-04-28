/****************************************************************************
** Meta object code from reading C++ file 'numpad_ui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../numpad_ui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'numpad_ui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_numpad_ui_t {
    QByteArrayData data[16];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_numpad_ui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_numpad_ui_t qt_meta_stringdata_numpad_ui = {
    {
QT_MOC_LITERAL(0, 0, 9), // "numpad_ui"
QT_MOC_LITERAL(1, 10, 18), // "numpadEnterClicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "on_btn1_2_clicked"
QT_MOC_LITERAL(4, 48, 15), // "on_btn2_clicked"
QT_MOC_LITERAL(5, 64, 15), // "on_btn3_clicked"
QT_MOC_LITERAL(6, 80, 15), // "on_btn4_clicked"
QT_MOC_LITERAL(7, 96, 15), // "on_btn5_clicked"
QT_MOC_LITERAL(8, 112, 15), // "on_btn6_clicked"
QT_MOC_LITERAL(9, 128, 15), // "on_btn7_clicked"
QT_MOC_LITERAL(10, 144, 15), // "on_btn8_clicked"
QT_MOC_LITERAL(11, 160, 15), // "on_btn9_clicked"
QT_MOC_LITERAL(12, 176, 15), // "on_btn0_clicked"
QT_MOC_LITERAL(13, 192, 19), // "on_btnClear_clicked"
QT_MOC_LITERAL(14, 212, 19), // "on_btnEnter_clicked"
QT_MOC_LITERAL(15, 232, 19) // "on_btnPiste_clicked"

    },
    "numpad_ui\0numpadEnterClicked\0\0"
    "on_btn1_2_clicked\0on_btn2_clicked\0"
    "on_btn3_clicked\0on_btn4_clicked\0"
    "on_btn5_clicked\0on_btn6_clicked\0"
    "on_btn7_clicked\0on_btn8_clicked\0"
    "on_btn9_clicked\0on_btn0_clicked\0"
    "on_btnClear_clicked\0on_btnEnter_clicked\0"
    "on_btnPiste_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_numpad_ui[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void numpad_ui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<numpad_ui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->numpadEnterClicked(); break;
        case 1: _t->on_btn1_2_clicked(); break;
        case 2: _t->on_btn2_clicked(); break;
        case 3: _t->on_btn3_clicked(); break;
        case 4: _t->on_btn4_clicked(); break;
        case 5: _t->on_btn5_clicked(); break;
        case 6: _t->on_btn6_clicked(); break;
        case 7: _t->on_btn7_clicked(); break;
        case 8: _t->on_btn8_clicked(); break;
        case 9: _t->on_btn9_clicked(); break;
        case 10: _t->on_btn0_clicked(); break;
        case 11: _t->on_btnClear_clicked(); break;
        case 12: _t->on_btnEnter_clicked(); break;
        case 13: _t->on_btnPiste_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (numpad_ui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&numpad_ui::numpadEnterClicked)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject numpad_ui::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_numpad_ui.data,
    qt_meta_data_numpad_ui,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *numpad_ui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *numpad_ui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_numpad_ui.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int numpad_ui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void numpad_ui::numpadEnterClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
