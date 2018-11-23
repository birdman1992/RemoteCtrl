#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QList>
#include <QStringList>
#include <QByteArray>
#include <QMap>
#include "updateitem.h"
#include "spddatagram.h"
#include "remoteclient.h"


class UpdateManager : public QObject
{
    Q_OBJECT
public:
    explicit UpdateManager(QObject *parent = NULL);
    QList<UpdateItem*> list_socket;
    void setRemoteNetwork(RemoteClient* c);
    void sendRemoteCmd(RemoteClient* c, QStringList params);

private:
    QStringList list_address;
    QUdpSocket* skt;
    SpdDataGram* dataManager;
    QMap< QString, RemoteClient*> list_client;

    void readDeviceList();
    void creatDevices(QStringList list);
    void msgPang(QString addr, quint16 port, QStringList& list);

private slots:
    void recvSktMsg();
    void newDataGram(QString addr, quint16 port, QByteArray dataGram);

signals:
    void newRemoteClient(RemoteClient*);
    void newCmdReturn(QString);

public slots:
    void scanDevices();
};

#endif // UPDATEMANAGER_H
