#include "AppData.hpp"

TableDataModel::TableDataModel()
{
}


int TableDataModel::rowCount(const QModelIndex & parent) const
{
    CConfigSchemaHelper *pSchemaHelper = CConfigSchemaHelper::getInstance();

    int nCount = pSchemaHelper->getElementArraySize(this->m_pActiveTable);

    return nCount;
}

int TableDataModel::columnCount(const QModelIndex & parent) const
{
    return 1;
}


QVariant TableDataModel::data(const QModelIndex & index, int role) const
{
    CConfigSchemaHelper *pSchemaHelper = CConfigSchemaHelper::getInstance();

    QHash<int, QByteArray> Roles = roleNames();

    const char *pValue = pSchemaHelper->getTableValue(Roles.value(role), index.row()+1);

    assert(pValue != NULL);

    return QString(pValue);
}

QHash<int, QByteArray> TableDataModel::roleNames() const
{
    static CConfigSchemaHelper *pSchemaHelper = CConfigSchemaHelper::getInstance();

    static QHash<int, QByteArray> Roles;

    for (int idx = 0; idx < pSchemaHelper->getEnvironmentXPathSize(); idx++)
    {
        const char *pRole =  pSchemaHelper->getEnvironmentXPaths(idx);
        Roles[Qt::UserRole + idx+1] = pRole;
    }

    return Roles;
}
