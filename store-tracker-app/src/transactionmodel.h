#ifndef TRANSACTIONMODEL_H
#define TRANSACTIONMODEL_H

#include <QAbstractItemModel>
#include "storemanager.h"

class TransactionModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit TransactionModel(StoreManager* mgr, QObject* parent = nullptr);
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return 4;
    }
    const QVector<Customer>& customers() const {
        return m_mgr->customers();}
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void refresh() {
        beginResetModel();
        endResetModel();
    }

private:
    StoreManager* m_mgr;
};
#endif
