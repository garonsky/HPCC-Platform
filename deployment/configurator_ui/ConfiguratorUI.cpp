#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QQmlContext>
#include <QObject>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include "ConfiguratorUI.hpp"
#include "AppData.hpp"

int main2(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;

    ApplicationData data;
    TableDataModel tableDataModel;


    view.rootContext()->setContextProperty("ApplicationData", &data);
    view.rootContext()->setContextProperty("tableDataModel", &tableDataModel);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl::fromLocalFile(*argv));
    view.show();


    return app.exec();
}

extern "C" void StartQMLUI(char* pQMLFile)
{
    main2(1,&pQMLFile);
}
