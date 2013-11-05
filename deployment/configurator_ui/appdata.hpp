#include <QObject>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QDateTime>
#include <QString>
#include "ConfigSchemaHelper.hpp"

class ApplicationData : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE QString getValue(QString XPath)
    {
        char pValue[1024];

        CConfigSchemaHelper *pSchemaHelper = CConfigSchemaHelper::getInstance();

        if (pSchemaHelper->getValue(XPath.toStdString().c_str(), pValue))
        {
            return pValue;
        }
    }
};
