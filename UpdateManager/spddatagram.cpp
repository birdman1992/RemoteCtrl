#include "spddatagram.h"


SpdDataGram::SpdDataGram(QObject *parent) : QObject(parent)
{
//    check_version();
}

void SpdDataGram::appendData(QString addr, QByteArray dataGram)
{
    qDebug()<<"[DataGram]"<<addr<<dataGram.right(dataGram.size()-20);
//    if(!dataMap.isEmpty())
    {
        QByteArray* pData = dataMap.value(addr, NULL);
        quint16 len;

        if(pData == NULL)
        {
            pData = new QByteArray(dataGram);
            dataMap.insert(addr, pData);
        }
        else
        {
            pData->append(dataGram);
        }

        if(pData->at(0) == '#' && pData->at(3) == '#')
        {
            len = (pData->at(1)<<8) + pData->at(2);
            if(pData->size()<len)
            {
                return;
            }
            else if(pData->size() >= len)
            {
                QByteArray qba = checkDataGram(pData->left(len));
                if(qba.isEmpty())
                    return;
                emit newDataGram(addr, qba);
            }
            delete pData;
            dataMap.insert(addr, NULL);
        }
    }
}



QByteArray SpdDataGram::check_version()
{
    QStringList cmdList;
    cmdList<<"CHECK"<<"VERSION";
    QByteArray qba = creatDataGram(cmdList);
    qDebug()<<"[check_version]"<<qba.remove(0,20);
    return qba;
}

QByteArray SpdDataGram::find_ping()
{
    QStringList cmdList;
    cmdList<<"PING";
    QByteArray qba = creatDataGram(cmdList);
    qDebug()<<"[find_ping]"<<qba.right(qba.size()-20);
    return qba;
}

QByteArray SpdDataGram::find_pang(QStringList netParams)
{
    QStringList cmdList;
    cmdList<<"PANG";
    QByteArray qba = creatDataGram(cmdList);
    qDebug()<<"[find_pang]"<<qba.right(qba.size()-20);
    return qba;
}

QByteArray SpdDataGram::check_network()
{
    QStringList cmdList;
    cmdList<<"CHECK"<<"NETWORK";
    QByteArray qba = creatDataGram(cmdList);
    qDebug()<<"[check_network]"<<qba.right(qba.size()-20);
    return qba;
}

QByteArray SpdDataGram::set_network(QStringList params)
{
    QStringList cmdList;
    cmdList<<"SET"<<"NETWORK"<<params;
    QByteArray qba = creatDataGram(cmdList);
    qDebug()<<"[set_network]"<<qba.right(qba.size()-20);
    return qba;
}

QByteArray SpdDataGram::checkDataGram(QByteArray qba)
{
    qba.remove(0,4);
    if(qba.size()<17)
        return QByteArray();

    QByteArray sign = qba.left(16);
    qba.remove(0,16);
    if(sign == QCryptographicHash::hash(qba + "rmxx@birdman", QCryptographicHash::Md5))
    {
        return qba;
    }

    return QByteArray();
}

QByteArray SpdDataGram::creatDataGram(QStringList cmds)
{
    QByteArray cmdPac = QByteArray("#") + cmds.join("#").toLocal8Bit();
    QByteArray sign = QCryptographicHash::hash(cmdPac + "rmxx@birdman", QCryptographicHash::Md5);
    quint16 len = cmdPac.size()+sign.size()+4;
    QByteArray ret = QByteArray("#00#");
    ret[1] = len>>8;
    ret[2] = len&0xff;
    ret += sign + cmdPac;
    return ret;
}
