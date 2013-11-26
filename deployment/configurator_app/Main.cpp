#include "MainWindow.hpp"
#include <QApplication>
#include <QThread>
#include "MainWindowThread.hpp"
#include <cstdlib>

#define CONFIGURATOR_STATIC_LIB
#include "../configurator/ConfiguratorAPI.hpp"


QApplication *pApp = NULL;
MainWindow *pMW = NULL;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    CONFIGURATOR_API::initialize();

    int nCount = CONFIGURATOR_API::getNumberOfAvailableComponents();

    for (int idx = 0; idx < nCount; idx++)
    {
        w.addComponentToList(const_cast<char*>(CONFIGURATOR_API::getComponentName(idx)));
    }

    nCount = CONFIGURATOR_API::getNumberOfAvailableServices();

    for (int idx = 0; idx < nCount; idx++)
    {
        w.addServiceToList(const_cast<char*>(CONFIGURATOR_API::getServiceName(idx)));
    }

    return a.exec();
}
