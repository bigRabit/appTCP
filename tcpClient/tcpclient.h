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
#include <QTreeWidget>
#include <QStringList>
#include <QHeaderView>

class tcpClient : public QWidget
{
	Q_OBJECT

public:
	tcpClient(QWidget *parent = 0, Qt::WFlags flags = 0);
	~tcpClient();

private:
	Ui::tcpClientClass ui;

	QTextEdit *messageText;
	QTreeWidget *fileWidget;
	
	QLabel *hostAddLabel;
	QLabel *portLabel;
	QLabel *statusLabel;
	QLineEdit *hostLineEdit;
	QLineEdit *portLineEdit;
	
	QTcpSocket *msgTcpSocket;
	QTcpSocket *fileTcpSocket;
	
	//QString message;
	quint16 blockSize;
	quint16 m_useless;

	QPushButton *connectButton;
	QPushButton *clearButton;
	QPushButton *closeButton;
	QPushButton *downLoadBotton;

	QGridLayout *mainLayout;

private slots:
	void newMsgConnect();
	void newFileConnect();
	void readMessage();
	void readFileMessage();
	void displayError(QAbstractSocket::SocketError);
	void getSocketState();
	void connectButtonClicked();
	//void clearTextEdit();
};

#endif // TCPCLIENT_H

