#ifndef UDPBROADCASTER_H
#define UDPBROADCASTER_H

#include <QThread>
class TransactionModel;

class UDPBroadcaster : public QThread {
    Q_OBJECT
public:
    explicit UDPBroadcaster(TransactionModel *model, QObject *parent = nullptr);
protected:
    void run() override;
private:
    TransactionModel *m_model;
};

#endif
