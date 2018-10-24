#ifndef UPDATEITEM_H
#define UPDATEITEM_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QStringList>

class UpdateItem : public QObject
{
    Q_OBJECT
public:
    UpdateItem(QString address, QObject *parent = NULL);
    UpdateItem(QUdpSocket* skt, QObject *parent = NULL);

    QString getVersion();
    QString getDepartName();
    QString getCabinetNum();
    QString getSocketAddress();

private:
    QUdpSocket* socket;
    bool isConnected;
    QString version;//版本号
    QString departName;//科室名称
    QString cabinetNum;//柜子编号
    QString socketAddress;//柜子IP

    void check(QString opt);

signals:
    void connected(bool);

public slots:

private slots:
    void socketStateChanged(QAbstractSocket::SocketState);
    void recvSockerData();
};

#endif // UPDATEITEM_H
