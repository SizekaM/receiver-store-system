#include "mainwindow.h"
#include "storemanager.h"
#include "transactionmodel.h"
#include "item.h"
#include "udpbroadcaster.h"

#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_manager(new StoreManager(this)),
    m_model(new TransactionModel(m_manager, this))
{
    // --- Central split: Items list on left, Transactions tree on right ---
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    auto *hl = new QHBoxLayout(central);

    // Items list
    m_itemModel = new QStringListModel(this);
    m_itemView  = new QListView(central);
    m_itemView->setModel(m_itemModel);
    hl->addWidget(m_itemView, /*stretch=*/1);

    // Transactions tree
    m_treeView = new QTreeView(central);
    m_treeView->setModel(m_model);
    hl->addWidget(m_treeView, /*stretch=*/3);

    // Populate items initially
    updateItemList();

    // --- Actions ---
    actionAddCustomer    = new QAction(tr("Add Customer"),    this);
    actionAddItem        = new QAction(tr("Add Item"),        this);
    actionNewTransaction = new QAction(tr("New Transaction"), this);
    actionBackup         = new QAction(tr("Backup"),          this);
    actionRestore        = new QAction(tr("Restore"),         this);
    actionBroadcast      = new QAction(tr("Broadcast"),       this);

    connect(actionAddCustomer,    &QAction::triggered, this, &MainWindow::addCustomer);
    connect(actionAddItem,        &QAction::triggered, this, &MainWindow::addItem);
    connect(actionNewTransaction, &QAction::triggered, this, &MainWindow::newTransaction);
    connect(actionBackup,         &QAction::triggered, this, &MainWindow::backup);
    connect(actionRestore,        &QAction::triggered, this, &MainWindow::restore);
    connect(actionBroadcast,      &QAction::triggered, this, &MainWindow::broadcast);

    // --- Menu Bar ---
    auto *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(actionBackup);
    fileMenu->addAction(actionRestore);
    fileMenu->addSeparator();
    fileMenu->addAction(actionBroadcast);

    auto *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("About"), this, &MainWindow::showAbout);

    // --- Tool Bar ---
    auto *tb = addToolBar(tr("Main"));
    tb->addAction(actionAddCustomer);
    tb->addAction(actionAddItem);
    tb->addAction(actionNewTransaction);
    tb->addAction(actionBroadcast);

    // --- Status Bar ---
    statusBar()->showMessage(tr("Ready"));
}

MainWindow::~MainWindow() = default;

void MainWindow::updateItemList()
{
    QStringList list;
    for (const Item &it : m_manager->items())
        list << it.name();
    m_itemModel->setStringList(list);
}

void MainWindow::addCustomer()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Add Customer"),
                                         tr("Customer Name:"),
                                         QLineEdit::Normal,
                                         QString(), &ok);
    if (!ok || name.isEmpty()) return;
    m_manager->addCustomer(name);
    m_model->refresh();
}

void MainWindow::addItem()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                         tr("Add Item"),
                                         tr("Item Name:"),
                                         QLineEdit::Normal,
                                         QString(), &ok);
    if (!ok || name.isEmpty()) return;

    QStringList types = { tr("Book"), tr("Magazine") };
    QString sel = QInputDialog::getItem(this,
                                        tr("Item Type"),
                                        tr("Type:"),
                                        types,
                                        /*current*/0,
                                        /*editable*/false,
                                        &ok);
    if (!ok) return;

    Item::Type t = (sel == tr("Book"))
                       ? Item::Book
                       : Item::Magazine;
    m_manager->addItem(name, t);

    updateItemList();
    m_model->refresh();
}

void MainWindow::newTransaction()
{
    bool ok;

    // 1) pick a customer
    QStringList custs;
    for (auto &c : m_manager->customers())
        custs << c.name();
    QString cust = QInputDialog::getItem(this,
                                         tr("New Transaction"),
                                         tr("Customer:"),
                                         custs, 0, false, &ok);
    if (!ok) return;

    // 2) pick an item
    QStringList items = m_itemModel->stringList();
    QString item = QInputDialog::getItem(this,
                                         tr("New Transaction"),
                                         tr("Item:"),
                                         items, 0, false, &ok);
    if (!ok) return;

    // 3) pick a quantity
    int qty = QInputDialog::getInt(this,
                                   tr("New Transaction"),
                                   tr("Quantity:"),
                                   /*value*/1, /*min*/1, /*max*/1000,
                                   /*step*/1, &ok);
    if (!ok) return;

    // 4) determine type string for your Transaction ctor
    QString typeStr;
    for (auto &it : m_manager->items()) {
        if (it.name() == item) {
            typeStr = (it.type() == Item::Book
                           ? tr("Book")
                           : tr("Magazine"));
            break;
        }
    }

    m_manager->addTransaction(cust, item, typeStr, qty);
    m_model->refresh();
}

void MainWindow::backup()
{
    m_manager->backup();
    m_model->refresh();
}

void MainWindow::restore()
{
    m_manager->restore();
    m_model->refresh();
}

void MainWindow::broadcast()
{
    auto *b = new UDPBroadcaster(m_model, this);
    b->start();
}

void MainWindow::showAbout()
{
    QMessageBox::about(this,
                       tr("About StoreTracker"),
                       tr("<h3>StoreTracker</h3>"
                          "<p>Version 1.0</p>"
                          "<p>Tracks purchases by customer.</p>"));
}
