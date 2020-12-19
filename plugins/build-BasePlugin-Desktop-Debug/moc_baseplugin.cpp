/****************************************************************************
** Meta object code from reading C++ file 'baseplugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BasePlugin/baseplugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'baseplugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BasePlugin_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BasePlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BasePlugin_t qt_meta_stringdata_BasePlugin = {
    {
QT_MOC_LITERAL(0, 0, 10) // "BasePlugin"

    },
    "BasePlugin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BasePlugin[] = {

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

void BasePlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject BasePlugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BasePlugin.data,
      qt_meta_data_BasePlugin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BasePlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BasePlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BasePlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IApplicationPlugin"))
        return static_cast< IApplicationPlugin*>(this);
    if (!strcmp(_clname, "ru.ltabs.plugins.IApplicationPlugin"))
        return static_cast< IApplicationPlugin*>(this);
    return QObject::qt_metacast(_clname);
}

int BasePlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xa8, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x94, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '#',  0x00, 'r',  'u',  '.',  'l',  't',  'a', 
    'b',  's',  '.',  'p',  'l',  'u',  'g',  'i', 
    'n',  's',  '.',  'I',  'A',  'p',  'p',  'l', 
    'i',  'c',  'a',  't',  'i',  'o',  'n',  'P', 
    'l',  'u',  'g',  'i',  'n',  0x00, 0x00, 0x00,
    0x1b, 0x0a, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x0a, 0x00, 'B',  'a',  's',  'e',  'P',  'l', 
    'u',  'g',  'i',  'n',  0xba, ' ',  0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00,
    0x05, 0x00, 'd',  'e',  'b',  'u',  'g',  0x00,
    0x15, 0x11, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    'x',  0x00, 0x00, 0x00, '@',  0x00, 0x00, 0x00,
    'l',  0x00, 0x00, 0x00, '\\', 0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xa8, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0x94, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    '#',  0x00, 'r',  'u',  '.',  'l',  't',  'a', 
    'b',  's',  '.',  'p',  'l',  'u',  'g',  'i', 
    'n',  's',  '.',  'I',  'A',  'p',  'p',  'l', 
    'i',  'c',  'a',  't',  'i',  'o',  'n',  'P', 
    'l',  'u',  'g',  'i',  'n',  0x00, 0x00, 0x00,
    0x15, 0x0a, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x9b, 0x0d, 0x00, 0x00,
    0x09, 0x00, 'c',  'l',  'a',  's',  's',  'N', 
    'a',  'm',  'e',  0x00, 0x0a, 0x00, 'B',  'a', 
    's',  'e',  'P',  'l',  'u',  'g',  'i',  'n', 
    '1',  0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0xba, ' ',  0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    '@',  0x00, 0x00, 0x00, '\\', 0x00, 0x00, 0x00,
    'x',  0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

QT_MOC_EXPORT_PLUGIN(BasePlugin, BasePlugin)

struct qt_meta_stringdata_BasePluginSettingsPage_t {
    QByteArrayData data[1];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BasePluginSettingsPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BasePluginSettingsPage_t qt_meta_stringdata_BasePluginSettingsPage = {
    {
QT_MOC_LITERAL(0, 0, 22) // "BasePluginSettingsPage"

    },
    "BasePluginSettingsPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BasePluginSettingsPage[] = {

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

void BasePluginSettingsPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject BasePluginSettingsPage::staticMetaObject = {
    { &ISettingsPage::staticMetaObject, qt_meta_stringdata_BasePluginSettingsPage.data,
      qt_meta_data_BasePluginSettingsPage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BasePluginSettingsPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BasePluginSettingsPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BasePluginSettingsPage.stringdata0))
        return static_cast<void*>(this);
    return ISettingsPage::qt_metacast(_clname);
}

int BasePluginSettingsPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ISettingsPage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_BasePluginWidgetPage_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BasePluginWidgetPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BasePluginWidgetPage_t qt_meta_stringdata_BasePluginWidgetPage = {
    {
QT_MOC_LITERAL(0, 0, 20) // "BasePluginWidgetPage"

    },
    "BasePluginWidgetPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BasePluginWidgetPage[] = {

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

void BasePluginWidgetPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject BasePluginWidgetPage::staticMetaObject = {
    { &IWidgetPage::staticMetaObject, qt_meta_stringdata_BasePluginWidgetPage.data,
      qt_meta_data_BasePluginWidgetPage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BasePluginWidgetPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BasePluginWidgetPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BasePluginWidgetPage.stringdata0))
        return static_cast<void*>(this);
    return IWidgetPage::qt_metacast(_clname);
}

int BasePluginWidgetPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IWidgetPage::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
