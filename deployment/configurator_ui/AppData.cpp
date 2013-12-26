#include "AppData.hpp"
#include <cassert>

static const int TOP_LEVEL = 1;
static void* P_TOP_LEVEL = (void*)(&TOP_LEVEL);

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

int ComponentDataModel::rowCount(const QModelIndex &parent) const
{
    int nRetVal = 0;

    void *pointer = parent.internalPointer();

    nRetVal = CONFIGURATOR_API::getNumberOfChildren(pointer);

    return nRetVal;
}

QVariant ComponentDataModel::data(const QModelIndex &index, int role) const
{
    const char *pName = CONFIGURATOR_API::getData(index.internalPointer());

    if (pName == NULL || Qt::DisplayRole != role)
    {
        return QVariant();
    }
    return QString(pName);
}

int ComponentDataModel::columnCount(const QModelIndex &/*parent*/) const
{
        return 1;
}

QModelIndex ComponentDataModel::parent(const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    /*if (index.internalPointer() == NULL || index.column() > 0)
    {
        createIndex(nParentRow, 0, (void*)NULL);
    }*/

    void *pParent = CONFIGURATOR_API::getParent(index.internalPointer());

    if (pParent == NULL)
    {
        return QModelIndex();
    }

    int nParentRow = CONFIGURATOR_API::getIndexFromParent(index.internalPointer());

    return createIndex(nParentRow, 0, pParent);
}

QModelIndex ComponentDataModel::index(int row, int column, const QModelIndex & parent) const
{
    if (column > 0)
    {
        return QModelIndex();
    }

    void *pPointer = NULL;

    pPointer = CONFIGURATOR_API::getChild(parent.internalPointer(), row);

    return createIndex(row, 0, pPointer);
}

Qt::ItemFlags ComponentDataModel::flags(const QModelIndex &index) const
{
    if (index.isValid() == false)
    {
        return 0;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ComponentDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        return QString("Components");
    return QAbstractItemModel::headerData(section, orientation, role);
}
