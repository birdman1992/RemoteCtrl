#include <QCoreApplication>
#include "updataclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UpdataClient* client = new UpdataClient();

    return a.exec();
}
