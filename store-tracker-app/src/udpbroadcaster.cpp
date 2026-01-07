#include "udpbroadcaster.h"
#include "transactionmodel.h"
#include "customer.h"
#include "transaction.h"

#include <QUdpSocket>
#include <QHostAddress>
#include <QXmlStreamWriter>

UDPBroadcaster::UDPBroadcaster(TransactionModel *model, QObject *parent)
    : QThread(parent)
    , m_model(model)
{}

void UDPBroadcaster::run() {
    // Prepare UDP socket
    QUdpSocket socket;
    socket.bind(QHostAddress::AnyIPv4, 0, QUdpSocket::ShareAddress);

    // Build XML
    QByteArray xml;
    QXmlStreamWriter writer(&xml);
    writer.writeStartDocument();
    writer.writeStartElement("store");

    for (const Customer &c : m_model->customers()) {
        writer.writeStartElement("customer");
        writer.writeAttribute("name", c.name());

        for (const Transaction &t : c.transactions()) {
            writer.writeStartElement("transaction");
            writer.writeAttribute("dateTime", t.dateTime().toString(Qt::ISODate));

            writer.writeStartElement("item");
            writer.writeAttribute("name",     t.itemName());
            writer.writeAttribute("type",     t.itemType());
            writer.writeAttribute("quantity", QString::number(t.quantity()));
            writer.writeEndElement(); // </item>

            writer.writeEndElement(); // </transaction>
        }

        writer.writeEndElement(); // </customer>
    }

    writer.writeEndElement(); // </store>
    writer.writeEndDocument();

    // Broadcast it on both localhost (for testing) and the LAN
    const quint16 port = 45454;
    socket.writeDatagram(xml, QHostAddress::LocalHost, port);
    socket.writeDatagram(xml, QHostAddress::Broadcast, port);
}
