#include "updatemanager.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

UpdateManager::UpdateManager(QObject *parent) : QObject(parent)
{
    skt = new QUdpSocket(this);
    skt->bind(QHostAddress::Any, 50013);
    connect(skt, SIGNAL(readyRead()), this, SLOT(recvSktMsg()));

    dataManager = new SpdDataGram(this);
    connect(dataManager, SIGNAL(newDataGram(QString, quint16,QByteArray)), this, SLOT(newDataGram(QString, quint16, QByteArray)));

    readDeviceList();
    creatDevices(list_address);
}

//ip<<xxx<<mac<<xxx<<mask<<xxx<<gateway<<xxx
void UpdateManager::setRemoteNetwork(RemoteClient *c)
{
    QStringList params;
    params<<"ip"<<c->ip<<"mac"<<c->mac<<"mask"<<c->mask<<"gateway"<<c->gateway;
    skt->writeDatagram(dataManager->set_network(params), QHostAddress(c->comAddr), c->comPort);
}

void UpdateManager::sendRemoteCmd(RemoteClient *c, QStringList params)
{
    skt->writeDatagram(dataManager->send_cmd(params), QHostAddress(c->comAddr), c->comPort);
}

void UpdateManager::readDeviceList()
{
    QFile devList(qApp->applicationDirPath()+"/device.ini");
    if(!devList.exists())
        return;
    devList.open(QIODevice::ReadOnly);

    list_address.clear();
    QByteArray qba;
    while(1)
    {
        qba = devList.readLine(20);
        qDebug()<<qba<<qba.isEmpty();
        if(qba.isEmpty())
            break;
        list_address<<QString(qba).remove('\n');
    }
    qDebug()<<"[address list]"<<list_address;
}

void UpdateManager::creatDevices(QStringList list)
{
    foreach(QString addr, list)
    {
        UpdateItem* item = new UpdateItem(addr);
        list_socket<<item;
    }
}

//   ip<<xxx<<mac<<xxx<<mask<<xxx<<gateway<<xxx
void UpdateManager::msgPang(QString addr, quint16 port, QStringList& list)
{
    if(list.isEmpty())
        return;

    RemoteClient* client = new RemoteClient();

    while(list.count() >1)
    {
        QString param = list.takeFirst();
        if(param == "ip")
        {
            client->ip = list.takeFirst();
        }
        else if(param == "mac")
        {
            client->mac = list.takeFirst();
        }
        else if(param == "mask")
        {
            client->mask = list.takeFirst();
        }
        else if(param == "gateway")
        {
            client->gateway = list.takeFirst();
        }
    }
//    list_client.insert(client->ip, client);
    client->comAddr = addr;
    client->comPort = port;
    emit newRemoteClient(client);
}

void UpdateManager::recvSktMsg()
{
    quint64 dataLen = 0;
    QByteArray qba;
    QHostAddress addr;
    quint16 port;

    if(skt->hasPendingDatagrams())
    {
        dataLen = skt->pendingDatagramSize();
        qba.resize(dataLen);
        skt->readDatagram(qba.data(), dataLen, &addr, &port);
        dataManager->appendData(addr.toString(), port, qba);
    }
}

void UpdateManager::scanDevices()
{
    skt->writeDatagram(dataManager->find_ping(), QHostAddress::Broadcast, 50010);
}

void UpdateManager::newDataGram(QString addr, quint16 port, QByteArray dataGram)
{
    qDebug()<<"[newDataGram]"<<addr<<dataGram;
    QStringList cmdList = QString::fromUtf8(dataGram).split('#',  QString::SkipEmptyParts);

    while(!cmdList.isEmpty())
    {
        QString cmd = cmdList.takeFirst();
        if(cmd == "PANG")
        {
            msgPang(addr, port, cmdList);
        }
        else if(cmd == "CMD_BACK")
        {
            emit newCmdReturn(cmdList.at(0));
        }
    }
}
