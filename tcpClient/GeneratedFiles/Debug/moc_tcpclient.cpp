/****************************************************************************
** Meta object code from reading C++ file 'tcpclient.h'
**
** Created: Thu Sep 17 09:46:41 2015
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tcpclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_tcpClient[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      27,   10,   10,   10, 0x08,
      44,   10,   10,   10, 0x08,
      58,   10,   10,   10, 0x08,
      76,   10,   10,   10, 0x08,
     119,   10,   10,   10, 0x08,
     136,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_tcpClient[] = {
    "tcpClient\0\0newMsgConnect()\0newFileConnect()\0"
    "readMessage()\0readFileMessage()\0"
    "displayError(QAbstractSocket::SocketError)\0"
    "getSocketState()\0connectButtonClicked()\0"
};

const QMetaObject tcpClient::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_tcpClient,
      qt_meta_data_tcpClient, 0 }
};

const QMetaObject *tcpClient::metaObject() const
{
    return &staticMetaObject;
}

void *tcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tcpClient))
	return static_cast<void*>(const_cast< tcpClient*>(this));
    return QWidget::qt_metacast(_clname);
}

int tcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newMsgConnect(); break;
        case 1: newFileConnect(); break;
        case 2: readMessage(); break;
        case 3: readFileMessage(); break;
        case 4: displayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: getSocketState(); break;
        case 6: connectButtonClicked(); break;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
