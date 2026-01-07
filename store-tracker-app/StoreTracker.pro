QT       += core gui widgets network
CONFIG   += c++17
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/storemanager.cpp \
    src/customer.cpp \
    src/item.cpp \
    src/transaction.cpp \
    src/transactionmodel.cpp \
    src/udpbroadcaster.cpp

HEADERS += \
    src/mainwindow.h \
    src/storemanager.h \
    src/customer.h \
    src/item.h \
    src/transaction.h \
    src/transactionmodel.h \
    src/udpbroadcaster.h
