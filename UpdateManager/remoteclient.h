#ifndef REMOTECLIENT_H
#define REMOTECLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

class RemoteClient : public QObject
{
    Q_OBJECT
public:
    explicit RemoteClient(QObject *parent = 0);
    QString ip;
    QString mac;
    QString mask;
    QString gateway;
    QString id;
    QString name;
    QString comAddr; //通信地址
    quint16 comPort; //通信端口
    QTcpSocket* comSkt;

signals:

public slots:
};

#endif // REMOTECLIENT_H
