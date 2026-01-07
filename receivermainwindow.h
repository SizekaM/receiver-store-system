#ifndef RECEIVERMAINWINDOW_H
#define RECEIVERMAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QUdpSocket>

class ReceiverMainWindow : public QMainWindow {
    Q_OBJECT
public:
    ReceiverMainWindow(QWidget *parent = nullptr);
private slots:
    void readPendingDatagrams();
private:
    QPlainTextEdit *m_textEdit;
    QUdpSocket     *m_socket;
};

#endif
