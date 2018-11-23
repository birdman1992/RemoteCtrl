#ifndef CTRLPROCESS_H
#define CTRLPROCESS_H

#include <QObject>
#include <QProcess>
#include <QStringList>
#include <QByteArray>

class CtrlProcess : public QObject
{
    Q_OBJECT
public:
    explicit CtrlProcess(QObject *parent = 0);
    void doCmd(QString cmd, QStringList params);
    void doCmd(QString cmd);
    QByteArray readAll();

private:
    QProcess process;
    QByteArray rst;

signals:
    void backMsg(QByteArray);

public slots:

private slots:
    void readCmdRst();
};

#endif // CTRLPROCESS_H
