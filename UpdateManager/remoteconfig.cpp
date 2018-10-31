#include "remoteconfig.h"
#include "ui_remoteconfig.h"

RemoteConfig::RemoteConfig(RemoteClient *c, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoteConfig)
{
    ui->setupUi(this);
    curClient = c;
    ui->ip->setText(c->ip);
    ui->mac->setText(c->mac);
    ui->mask->setText(c->mask);
    ui->gate->setText(c->gateway);
}

RemoteConfig::~RemoteConfig()
{
    delete ui;
}

void RemoteConfig::on_set_network_clicked()
{
    curClient->ip = ui->ip->text();
    curClient->mac = ui->mac->text();
    curClient->gateway = ui->gate->text();
    curClient->mask = ui->mask->text();
    emit setRemoteNetwork(curClient);
}
