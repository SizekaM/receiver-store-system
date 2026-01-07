#include <QApplication>
#include "receivermainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    ReceiverMainWindow w;
    w.show();
    return app.exec();
}
