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
	downLoadBotton = new QPushButton("Download");

	messageText = new QTextEdit(this);
	messageText->setText("hello world !");
	
	fileWidget = new QTreeWidget(this);
	fileWidget->setHeaderLabels(QStringList() << tr("File Name") << tr("Size") << tr("Created Time") << tr("LastModified Time"));
	fileWidget->header()->setResizeMode(QHeaderView::ResizeToContents );
	
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
	mainLayout->addWidget(fileWidget,8,0,5,4);
	mainLayout->addWidget(downLoadBotton,8,4);
	setLayout(mainLayout);	

	msgTcpSocket = new QTcpSocket(this);
	fileTcpSocket = new QTcpSocket(this);

	connect(msgTcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
	connect(msgTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
	connect(msgTcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(getSocketState()));

	connect(fileTcpSocket,SIGNAL(readyRead()),this,SLOT(readFileMessage()));

	connect(connectButton,SIGNAL(clicked()),this,SLOT(connectButtonClicked()));
	connect(clearButton,SIGNAL(clicked()),messageText,SLOT(clear()));
	connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
}

tcpClient::~tcpClient()
{

}
 
void tcpClient::newMsgConnect()
{
	blockSize = 0;

	msgTcpSocket->abort();

	//tcpSocket->connectToHost(hostLineEdit->text(),portLineEdit->text().toInt());
	msgTcpSocket->connectToHost(QHostAddress::LocalHost,23333);
	messageText->clear();
	qDebug() << msgTcpSocket->state();
}

void tcpClient::readMessage()
{
	QDataStream in(msgTcpSocket);
	in.setVersion(QDataStream::Qt_4_4);

    if(blockSize == 0) 
    {
       if(msgTcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
       in >> blockSize;
    }
    if(msgTcpSocket->bytesAvailable() < blockSize) 
    	return;

    //qDebug() << blockSize;
    
    QString message;
    in >> message;

    messageText->append(message);
   // in->remove(message);

    blockSize = 0;
}

void tcpClient::displayError(QAbstractSocket::SocketError)
{
	messageText->append(msgTcpSocket->errorString());
}

void tcpClient::connectButtonClicked()
{
	newMsgConnect();
	newFileConnect();
}

void tcpClient::getSocketState()
{
	switch(msgTcpSocket->state())
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

void tcpClient::newFileConnect()
{
	m_useless = 0;

	fileTcpSocket->abort();

	//tcpSocket->connectToHost(hostLineEdit->text(),portLineEdit->text().toInt());
	fileTcpSocket->connectToHost(QHostAddress::LocalHost,23334);
	fileWidget->clear();
	qDebug() << fileTcpSocket->state();
}

void tcpClient::readFileMessage()
{
	QDataStream filein(fileTcpSocket);
	filein.setVersion(QDataStream::Qt_4_4);
	
	if(m_useless == 0) 
	{
		if(fileTcpSocket->bytesAvailable() < (int)sizeof(quint16)) return;
		filein >> m_useless;
		qDebug() << m_useless;
	}

	if(fileTcpSocket->bytesAvailable() < m_useless) 
		return;

	//qDebug() << m_useless;
	//QByteArray qba = fileTcpSocket->readAll();
	//qDebug() << qba;
	QString message;
	filein >> message;
	//qDebug() << message;
	
	QStringList FileInfs = message.split("\n");

	QList<QTreeWidgetItem *> itemList;
	for (int i=1;i<15;i++)
	{
		QStringList FileInf = FileInfs.at(i).split("\t");

		QTreeWidgetItem *item = new QTreeWidgetItem;
		
		item->setText(0,FileInf.at(0));
		item->setText(1,FileInf.at(1));
		item->setText(2,FileInf.at(2));
		item->setText(3,FileInf.at(3));

		QPixmap pixmap("Resources/file.png");
		item->setIcon(0,pixmap);

		itemList.push_back(item);
	}
	fileWidget->addTopLevelItems(itemList);
	m_useless = 0;
}