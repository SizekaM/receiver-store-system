#include "storemanager.h"
#include "item.h"
#include "customer.h"
#include "transaction.h"

StoreManager::StoreManager(QObject *parent)
    : QObject(parent)
{}

void StoreManager::addCustomer(const QString &name) {
    // Simply append a new Customer by value
    m_customers.append(Customer(name));
}

void StoreManager::addItem(const QString &name, Item::Type type) {
    // Make an in-memory backup first
    backup();

    // Append an Item by value (no heap allocation)
    m_items.append(Item(name, type));
}

void StoreManager::addTransaction(const QString &cust,
                                  const QString &itemName,
                                  const QString &type,
                                  int qty) {
    // Find the customer and record the transaction
    for (Customer &c : m_customers) {
        if (c.name() == cust) {
            c.addTransaction(Transaction(itemName, type, qty));
            return;
        }
    }
}

QVector<Customer>& StoreManager::customers() {
    return m_customers;
}

QVector<Item>& StoreManager::items() {
    return m_items;
}

void StoreManager::backup() {
    m_backupCustomers = m_customers;
}

void StoreManager::restore() {
    m_customers = m_backupCustomers;
}
