#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->table_clinet->horizontalHeader()->setHighlightSections(false);
    ui->table_clinet->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
//        ui->table_clinet->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    manager = new UpdateManager(this);
    connect(ui->scanDevices, SIGNAL(clicked()), manager, SLOT(scanDevices()));
    connect(manager, SIGNAL(newRemoteClient(RemoteClient*)), this, SLOT(insertClinet(RemoteClient*)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::insertClinet(RemoteClient *c)
{
    int rowCount = ui->table_clinet->rowCount();

    ui->table_clinet->setRowCount(rowCount+1);
    ui->table_clinet->setItem(rowCount, 0, new QTableWidgetItem(c->id));
    ui->table_clinet->setItem(rowCount, 1, new QTableWidgetItem(c->name));
    ui->table_clinet->setItem(rowCount, 2, new QTableWidgetItem(c->mac));
    ui->table_clinet->setItem(rowCount, 3, new QTableWidgetItem(c->ip));
    list_client<<c;
}

void Widget::setRemoteNetwork(RemoteClient *c)
{
    manager->setRemoteNetwork(c);
}

void Widget::sendRemoteCmd(RemoteClient *c, QStringList params)
{
    manager->sendRemoteCmd(c, params);
}



void Widget::on_table_clinet_doubleClicked(const QModelIndex &index)
{
    winRemoteConfig = new RemoteConfig(list_client.at(index.row()));
    connect(winRemoteConfig, SIGNAL(setRemoteNetwork(RemoteClient*)), this, SLOT(setRemoteNetwork(RemoteClient*)));
    connect(winRemoteConfig, SIGNAL(remoteCmd(RemoteClient*,QStringList)), this, SLOT(sendRemoteCmd(RemoteClient*,QStringList)));
    connect(manager, SIGNAL(newCmdReturn(QString)), winRemoteConfig, SLOT(recvRemoteCmdReturn(QString)));
    winRemoteConfig->show();
}
