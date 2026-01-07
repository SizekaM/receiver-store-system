#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item {
public:
    enum Type { Book, Magazine };

    Item(const QString &name, Type t);

    QString name() const;
    Type    type() const;

private:
    QString m_name;
    Type    m_type;
};

#endif // ITEM_H
