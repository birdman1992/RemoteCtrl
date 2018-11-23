#include "ctrlprocess.h"
#include <QDebug>

CtrlProcess::CtrlProcess(QObject *parent) : QObject(parent)
{
    rst.clear();
    connect(&process, SIGNAL(readyRead()), this, SLOT(readCmdRst()));
}

void CtrlProcess::doCmd(QString cmd, QStringList params)
{
    rst.clear();
    process.start(cmd, params);
    process.waitForFinished(2000);
}

void CtrlProcess::doCmd(QString cmd)
{
    rst.clear();
    process.start(cmd);
    process.waitForFinished(2000);
}

QByteArray CtrlProcess::readAll()
{
    return rst;
}

void CtrlProcess::readCmdRst()
{
    QByteArray qba = process.readAll();
//    qDebug()<<QString::fromUtf8(qba);
    emit backMsg(qba);
}
