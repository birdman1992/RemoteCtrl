#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QObject>
#include <QUdpSocket>
#include <QList>
#include <QStringList>
#include <QByteArray>
#include "updateitem.h"
#include "spddatagram.h"


class UpdateManager : public QObject
{
    Q_OBJECT
public:
    explicit UpdateManager(QObject *parent = NULL);
    QList<UpdateItem*> list_socket;

private:
    QStringList list_address;
    QUdpSocket* skt;
    SpdDataGram* dataManager;

    void readDeviceList();
    void creatDevices(QStringList list);

private slots:
    void recvSktMsg();
    void newDataGram(QString addr, QByteArray dataGram);

signals:

public slots:
    void scanDevices();
};

#endif // UPDATEMANAGER_H
