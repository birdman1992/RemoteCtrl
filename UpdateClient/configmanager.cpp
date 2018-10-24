#include "configmanager.h"
#define INI_CABINET "/home/config/cabinet.ini"
#define INI_NETWORK "/home/config/network.ini"

ConfigManager* ConfigManager::m = new ConfigManager;

ConfigManager *ConfigManager::manager()
{
    return m;
}

ConfigManager::ConfigManager(QObject *parent) : QObject(parent)
{

}
