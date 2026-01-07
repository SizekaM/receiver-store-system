#include "receivermainwindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QHostAddress>
#include <QUdpSocket>

ReceiverMainWindow::ReceiverMainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_textEdit(new QPlainTextEdit(this)),
    m_socket(new QUdpSocket(this))
{
    // central widget
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    auto *lay = new QVBoxLayout(central);
    lay->addWidget(m_textEdit);
    m_textEdit->setReadOnly(true);

    // bind to the same port you’re broadcasting on, on both Any and Localhost
    const quint16 port = 45454;
    if (!m_socket->bind(
            QHostAddress::AnyIPv4,
            port,
            QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint
            )) {
        qWarning() << "UDP bind failed:" << m_socket->errorString();
    }


    connect(m_socket, &QUdpSocket::readyRead,
            this, &ReceiverMainWindow::readPendingDatagrams);

    // simple menu
    auto *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("Exit"), this, &QMainWindow::close);

    auto *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("About"), [this] {
        statusBar()->showMessage(tr("Receiver v1.0"), 2000);
    });

    statusBar()->showMessage(tr("Listening on port %1").arg(port), 5000);
}

void ReceiverMainWindow::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(m_socket->pendingDatagramSize()));
        m_socket->readDatagram(datagram.data(), datagram.size());
        m_textEdit->appendPlainText(QString::fromUtf8(datagram));
    }
}
