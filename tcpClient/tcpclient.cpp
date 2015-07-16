#include "tcpclient.h"

tcpClient::tcpClient(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	hostAddLabel = new QLabel(tr("Host Address: "));
	portLabel = new QLabel(tr("Port No. : "));
	hostLineEdit = new QLineEdit(this);
	portLineEdit = new QLineEdit(this);
	connectButton = new QPushButton("Connect");
	clearButton = new QPushButton("Clear");
	closeButton = new QPushButton("Close");

	messageText = new QTextEdit(this);
	messageText->setText("hello world !");

	mainLayout = new QGridLayout(this);

	mainLayout->addWidget(hostAddLabel,0,0);
	mainLayout->addWidget(hostLineEdit,0,1);
	mainLayout->addWidget(portLabel,0,2);
	mainLayout->addWidget(portLineEdit,0,3);
	mainLayout->addWidget(connectButton,0,4);
	mainLayout->addWidget(clearButton,1,4);
	mainLayout->addWidget(closeButton,2,4);
	mainLayout->addWidget(messageText,1,0,5,4);
	setLayout(mainLayout);	

	tcpSocket = new QTcpSocket(this);

	connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
	connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
	connect(connectButton,SIGNAL(clicked()),this,SLOT(connectButtonClicked()));
	connect(clearButton,SIGNAL(clicked()),messageText,SLOT(clear()));
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
}

tcpClient::~tcpClient()
{

}
 
void tcpClient::newConnect()
{
	blockSize = 1;

	tcpSocket->abort();

	//tcpSocket->connectToHost(hostLineEdit->text(),portLineEdit->text().toInt());
	tcpSocket->connectToHost(QHostAddress::LocalHost,23333);
}

void tcpClient::readMessage()
{
	QDataStream in(tcpSocket);
	in.setVersion(QDataStream::Qt_4_4);
 
	if(blockSize == 0)
	{
		if(tcpSocket->bytesAvailable() < (int)sizeof(quint16))
			return;
		in >> blockSize;
		//in >> m_useless;
	}

	if(tcpSocket->bytesAvailable() < blockSize)
		return ;
	
	char* buf;
	qDebug() << blockSize;
	in.readBytes(buf,(uint &)blockSize);
	qDebug() << blockSize;
	qDebug() << buf;
	QString message(buf);
	
	//in >> message;
	//qDebug() << blockSize;
	//qDebug() << message;
	//qDebug() << in ;
	messageText->append(message);
	blockSize = 0;
	delete buf;
	//qDebug() << in;
}

void tcpClient::displayError(QAbstractSocket::SocketError)
{
	messageText->append(tcpSocket->errorString());
}

void tcpClient::connectButtonClicked()
{
	newConnect();
}