#ifndef SPDDATAGRAM_H
#define SPDDATAGRAM_H

#include <QObject>
#include <QByteArray>
#include <QMap>
#include <QCryptographicHash>
#include <QStringList>
#include <QDebug>

class SpdDataGram : public QObject
{
    Q_OBJECT
public:
    explicit SpdDataGram(QObject *parent = NULL);
    void appendData(QString addr, quint16 port, QByteArray dataGram);
    QByteArray check_version();
    QByteArray find_ping();
    QByteArray find_pang(QStringList netParams);
    QByteArray check_network();
    QByteArray set_network(QStringList params);
    QByteArray send_cmd(QStringList params);

    QByteArray back_cmd(QStringList params);
private:
    QMap<QString, QByteArray*> dataMap;
    QByteArray checkDataGram(QByteArray qba);
    QByteArray creatDataGram(QStringList cmds);

signals:
    void newDataGram(QString addr, quint16 port, QByteArray dataGram);

public slots:
};

#endif // SPDDATAGRAM_H
