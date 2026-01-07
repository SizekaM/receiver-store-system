#include "transactionmodel.h"
#include <QVariant>

TransactionModel::TransactionModel(StoreManager* mgr, QObject* parent)
    : QAbstractItemModel(parent)
    , m_mgr(mgr)
{}

QModelIndex TransactionModel::index(int row, int column,
                                    const QModelIndex &parent) const {
    if (!parent.isValid()) {
        // top-level: customers
        if (row < m_mgr->customers().size())
            return createIndex(row, column, -1);
    } else if (parent.internalId() == -1) {
        // child: a transaction of customer at parent.row()
        const Customer &c = m_mgr->customers().at(parent.row());
        if (row < c.transactions().size())
            return createIndex(row, column, parent.row());
    }
    return QModelIndex();
}

QModelIndex TransactionModel::parent(const QModelIndex &child) const {
    if (child.internalId() == -1)
        return QModelIndex();
    // child.internalId() holds the parent customer index
    return createIndex(child.internalId(), 0, -1);
}

int TransactionModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid()) {
        return m_mgr->customers().size();
    } else if (parent.internalId() == -1) {
        return m_mgr->customers().at(parent.row()).transactions().size();
    }
    return 0;
}

QVariant TransactionModel::data(const QModelIndex &index, int role) const {
    if (role != Qt::DisplayRole || !index.isValid())
        return {};
    if (index.internalId() == -1) {
        // customer row
        if (index.column() == 0)
            return m_mgr->customers().at(index.row()).name();
    } else {
        const Transaction &t =
            m_mgr->customers().at(index.internalId()).transactions().at(index.row());
        switch (index.column()) {
        case 0: return t.dateTime().toString(Qt::ISODate);
        case 1: return t.itemName();
        case 2: return t.itemType();
        case 3: return t.quantity();
        }
    }
    return {};
}

QVariant TransactionModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};
    switch (section) {
    case 0: return "DateTime";
    case 1: return "Item";
    case 2: return "Type";
    case 3: return "Quantity";
    }
    return {};
}
