#include "updataclient.h"
#include "ctrlprocess.h"

UpdataClient::UpdataClient(QObject *parent) : QObject(parent)
{
    skt = new QUdpSocket();
    skt->bind(QHostAddress::Any, 50010);
    connect(skt, SIGNAL(readyRead()), this, SLOT(recvSktMsg()));

    devNetwork = new QNetInterface("eth0", this);

    qDebug()<<"listen 50010..";

    dataManager = new SpdDataGram(this);
    connect(dataManager, SIGNAL(newDataGram(QString,quint16,QByteArray)), this, SLOT(newDataGram(QString,quint16,QByteArray)));
}

void UpdataClient::msgBackPang()
{
    QStringList pangParams;
    pangParams<<"ip"<<devNetwork->ip();
    pangParams<<"mac"<<devNetwork->macAddress();
    pangParams<<"mask"<<devNetwork->netmask();
    pangParams<<"gateway"<<devNetwork->gateway();
    skt->writeDatagram(dataManager->find_pang(pangParams), serverAddr, serverPort);
}

void UpdataClient::msgBackCmd(QByteArray qba)
{
    QStringList msg;
    msg<<QString::fromUtf8(qba);

    skt->writeDatagram(dataManager->back_cmd(msg), serverAddr, serverPort);
}

void UpdataClient::cmdSet(QStringList &params)
{
    if(params.isEmpty())
        return;
    QString param = params.takeFirst();
    if(param == "NETWORK")
    {
        cmdSetNetwork(params);
    }
}

void UpdataClient::cmdSetNetwork(QStringList &params)
{
    if(params.isEmpty())
        return;

    while(params.count() > 2)
    {
        QString param = params.takeFirst();
        QString val = params.takeFirst();
        if(param == "ip")
        {
            devNetwork->setIp(val);
        }
        else if(param == "mac")
        {
            devNetwork->setMacAddress(val);
        }
        else if(param == "mask")
        {
            devNetwork->setNetmask(val);
        }
        else if(param == "gateway")
        {
            devNetwork->setGateway(val);
        }
    }
    params.clear();
    devNetwork->saveNetwork();
    msgBackPang();//以新的网络参数回应一次
}

void UpdataClient::cmdCheck(QStringList &params)
{

}

void UpdataClient::cmdExecute(QString cmd, QStringList params)
{
    CtrlProcess process;
    connect(&process, SIGNAL(backMsg(QByteArray)), this, SLOT(msgBackCmd(QByteArray)));
    process.doCmd(cmd, params);
}

void UpdataClient::recvSktMsg()
{
    quint64 dataLen = 0;
    QByteArray qba;

    if(skt->hasPendingDatagrams())
    {
        dataLen = skt->pendingDatagramSize();
        qba.resize(dataLen);
        skt->readDatagram(qba.data(), dataLen, &serverAddr, &serverPort);
        qDebug()<<"[recvSktMsg]"<<qba;
        dataManager->appendData(serverAddr.toString(), serverPort, qba);
    }
}

void UpdataClient::newDataGram(QString addr, quint16,  QByteArray dataGram)
{
    qDebug()<<"[newDataGram]"<<addr<<dataGram;
    QStringList cmdList = QString(dataGram).split('#',  QString::SkipEmptyParts);
    qDebug()<<"[cmdlist]"<<cmdList;

    while(!cmdList.isEmpty())
    {
        QString cmd = cmdList.takeFirst();
        qDebug()<<cmd;
        if(cmd == "PING")
        {
            msgBackPang();
        }
        else if(cmd == "SET")
        {
            cmdSet(cmdList);
        }
        else if(cmd == "CHECK")
        {
            cmdCheck(cmdList);
        }
        else if(cmd == "CMD")
        {
            QString cmd = cmdList.takeFirst();
            cmdExecute(cmd, cmdList);
        }
    }
}
