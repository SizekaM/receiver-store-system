#ifndef STOREMANAGER_H
#define STOREMANAGER_H

#include <QObject>
#include <QVector>
#include "customer.h"
#include "item.h"
#include "transaction.h"

class StoreManager : public QObject {
    Q_OBJECT
public:
    explicit StoreManager(QObject *parent = nullptr);

    /// Add a new customer (by name)
    void addCustomer(const QString &name);

    /// Add a new item (by name and type)
    void addItem(const QString &name, Item::Type type);

    /// Record a transaction against a customer
    void addTransaction(const QString &cust,
                        const QString &item,
                        const QString &type,
                        int qty);

    /// Accessors for the model
    QVector<Customer>& customers();
    QVector<Item>&     items();

    /// Backup / restore functionality
    void backup();
    void restore();

private:
    QVector<Customer> m_customers;
    QVector<Customer> m_backupCustomers;
    QVector<Item>     m_items;
};

#endif // STOREMANAGER_H
