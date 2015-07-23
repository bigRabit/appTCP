#include "tcpclient.h"

tcpClient::tcpClient(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	hostAddLabel = new QLabel(tr("Host Address: "));
	portLabel = new QLabel(tr("Port No. : "));
	statusLabel = new QLabel();
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
	mainLayout->addWidget(statusLabel,1,0,1,4);
	mainLayout->addWidget(clearButton,1,4);
	mainLayout->addWidget(closeButton,2,4);
	mainLayout->addWidget(messageText,2,0,5,4);
	setLayout(mainLayout);	

	tcpSocket = new QTcpSocket(this);

	connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
	connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
	connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(getSocketState()));
	connect(connectButton,SIGNAL(clicked()),this,SLOT(connectButtonClicked()));
	connect(clearButton,SIGNAL(clicked()),messageText,SLOT(clear()));
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
}

tcpClient::~tcpClient()
{

}
 
void tcpClient::newConnect()
{
	blockSize = 0;

	tcpSocket->abort();

	//tcpSocket->connectToHost(hostLineEdit->text(),portLineEdit->text().toInt());
	tcpSocket->connectToHost(QHostAddress::LocalHost,23333);
	messageText->clear();
	qDebug() << tcpSocket->state();
}

void tcpClient::readMessage()
{
	QDataStream in(tcpSocket);
	in.setVersion(QDataStream::Qt_4_4);

    if(blockSize == 0) 
    {
       if(tcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
       in >> blockSize;
    }
    if(tcpSocket->bytesAvailable() < blockSize) 
    	return;

    qDebug() << blockSize;
    
    QString message;
    in >> message;

    messageText->append(message);
   // in->remove(message);

    blockSize = 0;
}

void tcpClient::displayError(QAbstractSocket::SocketError)
{
	messageText->append(tcpSocket->errorString());
}

void tcpClient::connectButtonClicked()
{
	newConnect();
}

void tcpClient::getSocketState()
{
	switch(tcpSocket->state())
	{
		case QAbstractSocket::UnconnectedState:
         statusLabel->setText(tr("the Socket current state: unconnected state"));
         break;
      case QAbstractSocket::HostLookupState:
         statusLabel->setText(tr("the Socket current state: host lookup state"));
         break;
      case QAbstractSocket::ConnectingState:
         statusLabel->setText(tr("the Socket current state: connecting state"));
         break;
      case QAbstractSocket::ConnectedState:
         statusLabel->setText(tr("the Socket current state: connected state"));
         break;
      case QAbstractSocket::BoundState:
         statusLabel->setText(tr("the Socket current state: bound state"));
         break;
      case QAbstractSocket::ClosingState:
         statusLabel->setText(tr("the Socket current state: Closing state"));
         break;
      case QAbstractSocket::ListeningState:
         statusLabel->setText(tr("the Socket current state: Listening  state"));
         break;
      default:
         statusLabel->setText(tr("the Socket current state: Unknown state"));
         break;
	}
}