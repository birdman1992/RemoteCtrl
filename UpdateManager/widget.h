#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QModelIndex>
#include "updatemanager.h"
#include "remoteclient.h"
#include "remoteconfig.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void insertClinet(RemoteClient* c);
    void setRemoteNetwork(RemoteClient* c);

    void on_table_clinet_doubleClicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    QList<RemoteClient*> list_client;
    UpdateManager* manager;
    RemoteConfig* winRemoteConfig;
};

#endif // WIDGET_H
