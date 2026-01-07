#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDateTime>

class Transaction {
public:
    Transaction(const QString &item, const QString &type, int quantity,
                const QDateTime &dt = QDateTime::currentDateTime());
    QString itemName() const;
    QString itemType() const;
    int quantity() const;
    QDateTime dateTime() const;
private:
    QString m_item;
    QString m_type;
    int m_quantity;
    QDateTime m_datetime;
};

#endif
