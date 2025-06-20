#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "dialog.h"
#include "optiondialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->controlBtn, &QPushButton::clicked, this, &MainWindow::openDialog);
    connect(ui->scBtn, &QPushButton::clicked, this, &MainWindow::openOptionDialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: openDialog()
{
    // hide();
    dialogObj = new SecDialog();
    dialogObj->show();
}

void MainWindow :: openOptionDialog()
{
    opObj = new OptionDialog();
    opObj->open();
}
