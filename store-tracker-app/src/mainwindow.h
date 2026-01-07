#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QListView>
#include <QStringListModel>

class StoreManager;
class TransactionModel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void addCustomer();
    void addItem();
    void newTransaction();
    void backup();
    void restore();
    void broadcast();
    void showAbout();

private:
    /// Repopulate the left-hand QListView with m_manager->items()
    void updateItemList();

    StoreManager*      m_manager;
    TransactionModel*  m_model;

    QTreeView*         m_treeView;
    QListView*         m_itemView;
    QStringListModel*  m_itemModel;

    QAction* actionAddCustomer;
    QAction* actionAddItem;
    QAction* actionNewTransaction;
    QAction* actionBackup;
    QAction* actionRestore;
    QAction* actionBroadcast;
};

#endif // MAINWINDOW_H
