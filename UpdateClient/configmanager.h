#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>

class ConfigManager : public QObject
{
    Q_OBJECT
public:
    static ConfigManager* manager();

private:
    explicit ConfigManager(QObject *parent = NULL);
    static ConfigManager* m;

signals:

public slots:
};

#endif // CONFIGMANAGER_H
