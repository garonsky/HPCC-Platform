#include <QObject>
#include <QtQuick/QQuickView>
#include <QGuiApplication>
#include <QDateTime>
#include <QString>
#include <QAbstractListModel>
#include "ConfigSchemaHelper.hpp"

#define BUFFER_SIZE 2048

class TableDataModel : public QAbstractListModel
{
    Q_OBJECT

public:

    TableDataModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    int columnCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    QString getActiveTable()
    {
        return m_qstrActiveTable;
    }

    Q_INVOKABLE void setActiveTable(const QString &XPath)
    {
        m_qstrActiveTable = XPath;
        strncpy(m_pActiveTable, XPath.toStdString().c_str(), XPath.length());
        m_pActiveTable[XPath.length()] = 0;
    }

protected:

    QHash<int, QByteArray> roleNames() const;

private:

    QString m_qstrActiveTable;
    char m_pActiveTable[BUFFER_SIZE];
};

class ApplicationData : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE QString getValue(QString XPath)
    {
        char pValue[BUFFER_SIZE];

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
        char pValue[BUFFER_SIZE];

        CConfigSchemaHelper *pSchemaHelper = CConfigSchemaHelper::getInstance();

        return pSchemaHelper->getIndex(XPath.toStdString().c_str());
    }

    Q_INVOKABLE void  setIndex(QString XPath, int index)
    {
        CConfigSchemaHelper *pSchemaHelper = CConfigSchemaHelper::getInstance();

        return pSchemaHelper->setIndex(XPath.toStdString().c_str(), index);
    }
};
