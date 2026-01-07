#include "item.h"

// Match the two-argument constructor:
Item::Item(const QString &name, Item::Type t)
    : m_name(name),
    m_type(t)
{}

// Match the declaration for name()
QString Item::name() const {
    return m_name;
}

// And implement type():
Item::Type Item::type() const {
    return m_type;
}
