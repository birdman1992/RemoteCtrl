#ifndef REMOTECONFIG_H
#define REMOTECONFIG_H

#include <QWidget>
#include "remoteclient.h"

namespace Ui {
class RemoteConfig;
}

class RemoteConfig : public QWidget
{
    Q_OBJECT

public:
    explicit RemoteConfig(RemoteClient* c, QWidget *parent = 0);
    ~RemoteConfig();

public slots:
    void recvRemoteCmdReturn(QString msg);
signals:
    void setRemoteNetwork(RemoteClient* );
    void remoteCmd(RemoteClient* ,QStringList);

private slots:
    void on_set_network_clicked();

    void on_cmd_line_returnPressed();

private:
    Ui::RemoteConfig *ui;
    RemoteClient* curClient;
};

#endif // REMOTECONFIG_H
