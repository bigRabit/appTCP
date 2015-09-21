/********************************************************************************
** Form generated from reading ui file 'tcpclient.ui'
**
** Created: Wed Sep 16 10:28:20 2015
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcpClientClass
{
public:

    void setupUi(QWidget *tcpClientClass)
    {
    if (tcpClientClass->objectName().isEmpty())
        tcpClientClass->setObjectName(QString::fromUtf8("tcpClientClass"));
    tcpClientClass->resize(600, 400);

    retranslateUi(tcpClientClass);

    QMetaObject::connectSlotsByName(tcpClientClass);
    } // setupUi

    void retranslateUi(QWidget *tcpClientClass)
    {
    tcpClientClass->setWindowTitle(QApplication::translate("tcpClientClass", "tcpClient", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(tcpClientClass);
    } // retranslateUi

};

namespace Ui {
    class tcpClientClass: public Ui_tcpClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
