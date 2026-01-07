#include "transaction.h"

Transaction::Transaction(const QString &item, const QString &type, int quantity,
                         const QDateTime &dt)
    : m_item(item)
    , m_type(type)
    , m_quantity(quantity)
    , m_datetime(dt)
{}

QString Transaction::itemName() const { return m_item; }
QString Transaction::itemType() const { return m_type; }
int Transaction::quantity() const { return m_quantity; }
QDateTime Transaction::dateTime() const { return m_datetime; }
