#include "customer.h"

Customer::Customer(const QString &name)
    : m_name(name) {}

QString Customer::name() const { return m_name; }

QVector<Transaction> Customer::transactions() const { return m_transactions; }

void Customer::addTransaction(const Transaction &t) {
    m_transactions.append(t);
}
