#include "updatemanager.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

UpdateManager::UpdateManager(QObject *parent) : QObject(parent)
{
    skt = new QUdpSocket(this);
    skt->bind(QHostAddress::AnyIPv4, 50013);
    connect(skt, SIGNAL(readyRead()), this, SLOT(recvSktMsg()));

    dataManager = new SpdDataGram(this);

    readDeviceList();
    creatDevices(list_address);
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
        dataManager->appendData(addr.toString(), qba);
    }
}

void UpdateManager::scanDevices()
{
    skt->writeDatagram(dataManager->find_ping(), QHostAddress::Broadcast, 50010);
}

void UpdateManager::newDataGram(QString addr, QByteArray dataGram)
{
    qDebug()<<"[newDataGram]"<<addr<<dataGram;
    QStringList cmdList = QString(dataGram).split('#',  QString::SkipEmptyParts);

    while(!cmdList.isEmpty())
    {
        QString cmd = cmdList.takeFirst();
        if(cmd == "PANG")
        {

        }
    }
}
