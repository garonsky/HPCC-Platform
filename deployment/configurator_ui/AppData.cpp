#include "AppData.hpp"
#include <cassert>

TableDataModel::TableDataModel()
{
}

int TableDataModel::rowCount(const QModelIndex& /*parent*/) const
{
    int nCount = CONFIGURATOR_API::getNumberOfRows(this->m_pActiveTable);

    return nCount;
}

int TableDataModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 1;
}

QVariant TableDataModel::data(const QModelIndex & index, int role) const
{
    QHash<int, QByteArray> Roles = roleNames();

    const char *pValue  = CONFIGURATOR_API::getTableValue(Roles.value(role), index.row()+1);

    assert(pValue != NULL);

    return QString(pValue);
}

QHash<int, QByteArray> TableDataModel::roleNames() const
{
    static QHash<int, QByteArray> Roles;

    int nColumns = CONFIGURATOR_API::getNumberOfUniqueColumns();

    for (int idx = 0; idx < nColumns; idx++)
    {
        const char *pRole =  CONFIGURATOR_API::getColumnName(idx);
        Roles[Qt::UserRole + idx+1] = pRole;
    }

    return Roles;
}
