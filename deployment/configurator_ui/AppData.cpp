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


ComponentDataModel::ComponentDataModel( QObject *parent) : QAbstractItemModel(parent)
{
}

int ComponentDataModel::rowCount(const QModelIndex & /*parent */) const
{
    return CONFIGURATOR_API::getNumberOfComponentsInConfiguration();
}

QVariant ComponentDataModel::data(const QModelIndex &index, int role) const
{
    const char *pName = CONFIGURATOR_API::getComponentNameInConfiguration(index.row()-1);

    //assert(pName != NULL);

    if (pName == NULL || Qt::DisplayRole != role)
    {
        return QVariant();
    }
    return QString(pName);
}

int ComponentDataModel::columnCount(const QModelIndex & /* parent */) const
{
    return 1;
}


QModelIndex ComponentDataModel::parent(const QModelIndex & index) const
{
    if (index.row() <= 0 || index.row()  >= CONFIGURATOR_API::getNumberOfComponentsInConfiguration())
    {
        return QModelIndex();
    }

    //return createIndex(QModelIndex().row()-1, 1);
    return createIndex(QModelIndex().row(), 1);
}

QModelIndex ComponentDataModel::index(int row, int column, const QModelIndex & parent) const
{
    if (row < 0 || row >= CONFIGURATOR_API::getNumberOfComponentsInConfiguration())
    {
        return QModelIndex();
    }
    //return createIndex(row+1, 1);
    return createIndex(QModelIndex().row(), 1);
}

Qt::ItemFlags ComponentDataModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ComponentDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QString("Header");
}
