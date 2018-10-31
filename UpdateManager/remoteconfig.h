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

signals:
    void setRemoteNetwork(RemoteClient* );

private slots:
    void on_set_network_clicked();

private:
    Ui::RemoteConfig *ui;
    RemoteClient* curClient;
};

#endif // REMOTECONFIG_H
