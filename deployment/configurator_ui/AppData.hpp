#include <QObject>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QDateTime>
#include <QString>
#include <QAbstractListModel>
#include "ConfigSchemaHelper.hpp"

class TableDataModel : public QAbstractListModel
{
    Q_OBJECT

public:

    TableDataModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    int columnCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:

    QHash<int, QByteArray> roleNames() const;

private:
};

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
