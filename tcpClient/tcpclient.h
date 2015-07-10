#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QtGui/QWidget>
#include "ui_tcpclient.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QtNetWork>
#include <QTextEdit>
#include <QGridLayout>

class tcpClient : public QWidget
{
	Q_OBJECT

public:
	tcpClient(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tcpClient();

private:
	Ui::tcpClientClass ui;

	QTextEdit *messageText;
	
	QLabel *hostAddLabel;
	QLabel *portLabel;
	QLineEdit *hostLineEdit;
	QLineEdit *portLineEdit;
	QTcpSocket *tcpSocket;
	QString message;
	quint16 blockSize;
	QPushButton *connectButton;

	QGridLayout *mainLayout;

private slots:
	void newConnect();
	void readMessage();
	void displayError(QAbstractSocket::SocketError);
	void connectButtonClicked();
};

#endif // TCPCLIENT_H
