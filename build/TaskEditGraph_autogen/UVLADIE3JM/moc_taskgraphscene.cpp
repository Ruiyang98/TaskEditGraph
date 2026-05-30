/****************************************************************************
** Meta object code from reading C++ file 'taskgraphscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/taskgraphscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'taskgraphscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TaskGraphScene_t {
    QByteArrayData data[11];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaskGraphScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaskGraphScene_t qt_meta_stringdata_TaskGraphScene = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TaskGraphScene"
QT_MOC_LITERAL(1, 15, 11), // "onTaskAdded"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "index"
QT_MOC_LITERAL(4, 34, 13), // "onTaskRemoved"
QT_MOC_LITERAL(5, 48, 13), // "onTaskUpdated"
QT_MOC_LITERAL(6, 62, 18), // "onConditionChanged"
QT_MOC_LITERAL(7, 81, 9), // "onAddTask"
QT_MOC_LITERAL(8, 91, 10), // "onEditTask"
QT_MOC_LITERAL(9, 102, 12), // "onDeleteTask"
QT_MOC_LITERAL(10, 115, 14) // "onSetCondition"

    },
    "TaskGraphScene\0onTaskAdded\0\0index\0"
    "onTaskRemoved\0onTaskUpdated\0"
    "onConditionChanged\0onAddTask\0onEditTask\0"
    "onDeleteTask\0onSetCondition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskGraphScene[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    1,   57,    2, 0x08 /* Private */,
       5,    1,   60,    2, 0x08 /* Private */,
       6,    1,   63,    2, 0x08 /* Private */,
       7,    1,   66,    2, 0x08 /* Private */,
       8,    1,   69,    2, 0x08 /* Private */,
       9,    1,   72,    2, 0x08 /* Private */,
      10,    1,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void TaskGraphScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TaskGraphScene *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onTaskAdded((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onTaskRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onTaskUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onConditionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onAddTask((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onEditTask((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onDeleteTask((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onSetCondition((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TaskGraphScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_TaskGraphScene.data,
    qt_meta_data_TaskGraphScene,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TaskGraphScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskGraphScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TaskGraphScene.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int TaskGraphScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
