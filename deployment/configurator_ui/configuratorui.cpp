#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include "configuratorui.hpp"
#include <QQmlContext>

#include <QObject>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QDateTime>
//#include "./moc_configuratorui.moc"
/*ConfiguratorUI::ConfiguratorUI(QObject *parent) :
    QObject(parent)
{
}*/


class ApplicationData : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE QDateTime getCurrentDateTime() const {
        return QDateTime::currentDateTime();
    }
    //ApplicationData(){}
    //virtual ~ApplicationData(){}
};

int main2(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;

    ApplicationData data;

    //qmlRegisterType<ApplicationData>("");
    view.rootContext()->setContextProperty("ApplicationData", &data);
    //view.rootContext()->set
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl::fromLocalFile("MyItem.qml"));
    view.show();
    return app.exec();
}

extern "C" void StartQMLUI()
{
    main2(0,NULL);
}
