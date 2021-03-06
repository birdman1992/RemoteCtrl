#ifndef UPDATACLIENT_H
#define UPDATACLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QDebug>
#include "../UpdateManager/spddatagram.h"
#include "qnetinterface.h"

class UpdataClient : public QObject
{
    Q_OBJECT
public:
    explicit UpdataClient(QObject *parent = NULL);

private:
    QUdpSocket* skt;
    SpdDataGram* dataManager;
    QNetInterface* devNetwork;
    QHostAddress serverAddr;
    quint16 serverPort;

    void msgBackPang();
    void cmdSet(QStringList& params);
    void cmdSetNetwork(QStringList& params);
    void cmdCheck(QStringList& params);
    void cmdExecute(QString cmd, QStringList params);


signals:

public slots:

private slots:
    void recvSktMsg();
    void newDataGram(QString addr, quint16 port, QByteArray dataGram);
    void msgBackCmd(QByteArray qba);
};

#endif // UPDATACLIENT_H
