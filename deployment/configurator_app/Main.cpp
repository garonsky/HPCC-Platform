#include "MainWindow.hpp"
#include <QApplication>
#include <QThread>
//#include "MainWindowInterface.h"
#include "MainWindowThread.hpp"
#include "../configurator/ConfigSchemaHelper.hpp"
#include "jstring.hpp"


QApplication *pApp = NULL;
MainWindow *pMW = NULL;


int main(int argc, char *argv[])
{
    InitModuleObjects();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    CConfigSchemaHelper *pSchemaHelper = CConfigSchemaHelper::getInstance();
    pSchemaHelper->populateSchema();
    pSchemaHelper->processExtensionArr();
    pSchemaHelper->processAttributeGroupArr();
    pSchemaHelper->populateEnvXPath();

    StringArray strBuildSet;


    StringArray arrXSDs;
    arrXSDs.append("dali.xsd");
    //arrXSD.append(");
    //pSchemaHelper->setBuildSetArray(arrXSDs);
    pSchemaHelper->populateBuildSet();
    pSchemaHelper->getBuildSetComponents(strBuildSet);

    int nCount = strBuildSet.length();

    for (int idx = 0; idx < nCount; idx++)
    {
        w.addComponentToList(const_cast<char*>(strBuildSet.item(idx)));
    }



    return a.exec();
}
/*
extern "C" int StartMainWindowUI(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
    pMW = new MainWindow();

    MainWindowThread *pUIThread = new MainWindowThread(pMW);
    pUIThread->SetApplication(&app);
    //pUIThread->start();
    pUIThread->run();
    pUIThread->m_pApplication->exec();
    return 1;
}

extern "C" void SetComponentList(int nCount, const char *pComponentList[])
{
    pMW->setComponentList(nCount, const_cast<char**>(pComponentList));
}

extern "C" void AddComponentToList(const char *pComponent)
{
    pMW->addComponentToList(const_cast<char*>(pComponent));
}

extern "C" void SetServiceList(int argc, char *pServiceList[])
{

}

extern "C" int ShowMainWindowUI()
{
    pMW->show();

    return pApp->exec();
}
*/
