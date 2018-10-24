#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    manager = new UpdateManager(this);
    connect(ui->scanDevices, SIGNAL(clicked()), manager, SLOT(scanDevices()));
}

Widget::~Widget()
{
    delete ui;
}
