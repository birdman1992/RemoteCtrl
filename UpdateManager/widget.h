#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "updatemanager.h"

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

private:
    Ui::Widget *ui;
    UpdateManager* manager;
};

#endif // WIDGET_H
