#include "updateitem.h"
#include <QDebug>

UpdateItem::UpdateItem(QString address, QObject *parent):QObject(parent)
{
    socket = new QUdpSocket();
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(recvSockerData()));
    socket->connectToHost(QHostAddress(address), 4399);
    socketAddress = address;
}

UpdateItem::UpdateItem(QUdpSocket *skt, QObject *parent)
{
    socket = skt;
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(recvSockerData()));
    socketAddress = socket->peerAddress().toString();
}

QString UpdateItem::getVersion()
{
    return version;
}

QString UpdateItem::getDepartName()
{
    return departName;
}

QString UpdateItem::getCabinetNum()
{
    return cabinetNum;
}

QString UpdateItem::getSocketAddress()
{
    return socketAddress;
}

void UpdateItem::socketStateChanged(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::UnconnectedState)
    {
        isConnected = false;
        emit connected(false);
    }
    else if(state == QAbstractSocket::ConnectedState)
    {
        isConnected = true;
        emit connected(true);
    }
}

void UpdateItem::check(QString opt)
{
    QByteArray qba = QString("#check#%1#").arg(opt).toLocal8Bit();
    socket->write(qba);
    qDebug()<<"[>>>]"<<qba;
}

/*
#check#A#
A:1 info

#report#A#
A:1 version, 2 departName, 3 cabinetNum

#exe#A#
A:执行的动作 1 update, 2 download

*/
void UpdateItem::recvSockerData()
{
    QByteArray qba = socket->readAll();
    qDebug()<<"[4399 recv]"<<qba;
    QStringList params = QString(qba).split("#", QString::SkipEmptyParts);
    if(params.isEmpty())
        return;

    if(params.at(0) == "report")
    {
        if(params.count() != 4)
            return;

        version = params.at(1);
        departName = params.at(2);
        cabinetNum = params.at(3);
    }
}
