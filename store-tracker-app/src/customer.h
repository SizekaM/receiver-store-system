#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QVector>
#include "transaction.h"

class Customer {
public:
    Customer(const QString &name);
    QString name() const;
    QVector<Transaction> transactions() const;
    void addTransaction(const Transaction &t);
private:
    QString m_name;
    QVector<Transaction> m_transactions;
};
#endif
