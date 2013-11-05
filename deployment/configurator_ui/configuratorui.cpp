#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include "configuratorui.hpp"
#include <QQmlContext>

#include <QObject>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include "appdata.hpp"

int main2(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;

    ApplicationData data;


    view.rootContext()->setContextProperty("ApplicationData", &data);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl::fromLocalFile(*argv));
    view.show();


    return app.exec();
}

extern "C" void StartQMLUI(char* pQMLFile)
{
    main2(1,&pQMLFile);
}
