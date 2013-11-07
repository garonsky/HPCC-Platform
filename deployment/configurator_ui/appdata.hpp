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

    Q_INVOKABLE void setValue(QString XPath, QString qstrNewValue)
    {

        CConfigSchemaHelper *pSchemaHelper = CConfigSchemaHelper::getInstance();

        pSchemaHelper->setValue(XPath.toStdString().c_str(), qstrNewValue.toStdString().c_str());
    }

    Q_INVOKABLE int getIndex(QString XPath)
    {
        char pValue[1024];

        CConfigSchemaHelper *pSchemaHelper = CConfigSchemaHelper::getInstance();

        return pSchemaHelper->getIndex(XPath.toStdString().c_str());
    }

    Q_INVOKABLE void  setIndex(QString XPath, int index)
    {
        CConfigSchemaHelper *pSchemaHelper = CConfigSchemaHelper::getInstance();

        return pSchemaHelper->setIndex(XPath.toStdString().c_str(), index);
    }
};
